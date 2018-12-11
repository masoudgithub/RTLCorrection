#include "genOCM.h"
#include <string>
#include <fstream>

void fillOCMRowNodes(const char *fileName, nodeMap &ocmNodeMap)
{

    std::string line;
    std::ifstream schematicFile (fileName);

    if (schematicFile.is_open())
    {
        std::cout<<"schematicFile file is open for the first time in fillRowNodes"<<std::endl;
        while (getline (schematicFile,line))
        {
            OCMNode tempNode;
            if(line.find("->",0) > 10000)
            {
                // find alias
                std::size_t pos1 = 0;
                std::size_t pos2 = line.find(" ");
                tempNode.alias = line.substr(pos1,pos2-pos1);
                //std::cout<<"rowNodes[node].alias = "<<tempNode.alias<<std::endl;
                // find name
                pos1 = line.find("\"",0);
                pos2 = line.find("\"",pos1+1);
                if ((pos1 < 1000) && (pos2 < 1000))
                {
                    tempNode.name = line.substr(pos1+1,pos2-pos1-1);
                }
                else
                {
                    tempNode.name = "";
                }
                //std::cout<<"rowNodes[node].name = "<<tempNode.name<<std::endl;

                // find type
                if (tempNode.name.find("$add") < 1000)
                {
                    tempNode.type = "add";
                }
                else if (tempNode.name.find("clk") < 1000)
                {
                    tempNode.type = "clkPort";
                }
                else if (tempNode.name.find("memory_controller") < 1000)
                {
                    tempNode.type = "memory_controller";
                }
                else if (tempNode.name.find("$mul") < 1000)
                {
                    tempNode.type = "mul";
                }
                else if (tempNode.name.find("$sub") < 1000)
                {
                    tempNode.type = "sub";
                }
                else if (tempNode.name.find("reg") < 1000)
                {
                    tempNode.type = "reg";
                }
                else if (tempNode.name.find("$dff") < 1000)
                {
                    tempNode.type = "dff";
                }
                else if (tempNode.name.find("$pmux") < 1000)
                {
                    tempNode.type = "pmux";
                }
                else if (tempNode.name.find("$mux") < 1000)
                {
                    tempNode.type = "mux";
                }
                else if (tempNode.name.find("$and") < 1000)
                {
                    tempNode.type = "and";
                }
                else if (tempNode.name.find("$not") < 1000)
                {
                    tempNode.type = "not";
                }
                else if (tempNode.name.find("$reduce_or") < 1000)
                {
                    tempNode.type = "reduce_or";
                }
                else if (tempNode.name.find("$or") < 1000)
                {
                    tempNode.type = "or";
                }
                else if (tempNode.name.find("$eq") < 1000)
                {
                    tempNode.type = "eq";
                }
                else if (tempNode.name.find("BUF") < 1000)
                {
                    tempNode.type = "BUF";
                }
                else if (line.find("shape=octagon") < 1000)
                {
                    tempNode.type = "port";
                }
                else if ((tempNode.name.find("_bit") < 1000) && (tempNode.type != "reg"))
                {
                    tempNode.type = "wire";
                }
                else if ((tempNode.name.find("<s") < 1000))
                {
                    tempNode.type = "wire";
                }
                else if ((tempNode.alias.find("v") < 1000))
                {
                    tempNode.type = "value";
                }
                else
                {  
                    tempNode.type = "NON";
                }
                //finding ports A, B, D, S, CLK
                findPort(line,tempNode);
                ocmNodeMap.insert(std::pair<std::string,OCMNode>(tempNode.alias,tempNode));
            }
        }
        schematicFile.close();
    }

    for (auto& it: ocmNodeMap)
    {
        //std::cout<<"alias= "<<it.first<<"\n";
        //std::cout<<"name = "<<it.second.name<<std::endl;
        //std::cout<<"type = "<<it.second.type<<std::endl;
        //std::cout<<std::endl;
    }
}

void findConnections(const char *fileName, std::map <std::string, OCMNode> &ocmNodeMap)
{
    std::string line;
    std::ifstream schematicFile;
    OCMNode tempNode;
    size_t pos1, pos2, pos3, pos4;
    std::string parentNodeAlias;
    std::string childNodeAlias;
    // finding number of inputs for each node at the first pass
    schematicFile.open(fileName,std::ifstream::in);
    if (schematicFile.is_open())
    {
        std::cout<<"schematicFile file is open for the first time findConnections"<<std::endl;
        while (getline (schematicFile,line))
        {
            if(line.find("->") < 1000)// the line shows connection if there is a "->"
            {
                //std::cout<<line<<std::endl;
                pos1 = line.find(":"); // the parent node marker
                pos2 = line.find(" "); // the first space
                pos3 = line.find(" ",pos2+1); // the second space
                pos4 = line.find(":",pos3+1); // the child node marker
                parentNodeAlias = line.substr(0,pos1);
                childNodeAlias = line.substr(pos3+1,pos4-pos3-1);
                //std::cout << "" << "" << parentNodeAlias <<std::endl;
                nodeMap::iterator it = ocmNodeMap.find(childNodeAlias);
                if (it != ocmNodeMap.end())
                {
                    if (isItDataConnection(line, childNodeAlias, ocmNodeMap))
                    {
                        tempNode = it->second;
                        tempNode.numberOfInputs++;
                        ocmNodeMap.at(childNodeAlias) = tempNode;
                    }
                }
            }
        }
    }
    schematicFile.close();

// creating input names aliases
    for (auto& it: ocmNodeMap)
    {
        it.second.inputAliases = new std::string[it.second.numberOfInputs];
        it.second.inputNames   = new std::string[it.second.numberOfInputs];
        it.second.inputTypes   = new std::string[it.second.numberOfInputs];
    }

// filling the inputs and sliases during the second pass
    schematicFile.open(fileName,std::ifstream::in);
    if (schematicFile.is_open())
    {
        std::cout<<"schematicFile file is open for the second time in findConnections"<<std::endl;
        while (getline (schematicFile,line))
        {
            if(line.find("->") < 1000)// the line shows connection if there is a "->"
            {
                //std::cout<<line<<std::endl;
                pos1 = line.find(":"); // the parent node marker
                pos2 = line.find(" "); // the first space
                pos3 = line.find(" ",pos2+1); // the second space
                pos4 = line.find(":",pos3+1); // the child node marker
                parentNodeAlias = line.substr(0,pos1);
                childNodeAlias = line.substr(pos3+1,pos4-pos3-1);
                //std::cout << "" << "" << parentNodeAlias <<std::endl;
                nodeMap::iterator it = ocmNodeMap.find(childNodeAlias);
                if (it != ocmNodeMap.end())
                {
                    tempNode = it->second;
                    nodeMap::iterator pit = ocmNodeMap.find(parentNodeAlias);
                    if (pit != ocmNodeMap.end())
                    {
                       if (isItDataConnection(line, childNodeAlias, ocmNodeMap))
                        {
                            tempNode.inputAliases[tempNode.inputIndex] = pit->second.alias;
                            tempNode.inputNames[tempNode.inputIndex] = pit->second.name;
                            tempNode.inputTypes[tempNode.inputIndex] = pit->second.type;
                            tempNode.inputIndex++;
                        }
                    }
                    ocmNodeMap.at(childNodeAlias) = tempNode;
                }
            }
        }
    }
    else
    {
        std::cout<<"Error: cannot open the dot file!";
    }
    schematicFile.close();

    for (auto& it: ocmNodeMap)
    {
        //std::cout<<"alias= "<<it.first<<"\n";
        //std::cout<<"name = "<<it.second.name<<std::endl;
        //std::cout<<"type = "<<it.second.type<<std::endl;
        //std::cout<<"numInputs = "<<it.second.numberOfInputs<<std::endl<<std::endl;
        for ( int i = 0; i < it.second.numberOfInputs; i++)
        {
            //std::cout<<"inputAlias "<<i<<" = "<<it.second.inputAliases[i]<<std::endl;
            //std::cout<<"inputName  "<<i<<" = "<<it.second.inputNames[i]<<std::endl;
            //std::cout<<"inputType  "<<i<<" = "<<it.second.inputTypes[i]<<std::endl<<std::endl;
        }
        //std::cout<<std::endl;
    }
}

int returnNumberOfreducedNodes(std::map <std::string, OCMNode> &ocmNodeMap, std::map <std::string, OCMNode> &reducedNodeMap)
{
    OCMNode tempNode;

    for (auto& n: ocmNodeMap)
    {
        if( isItMainType(n.second.type))
        {
            tempNode = n.second;
            reducedNodeMap.insert(std::pair<std::string,OCMNode>(tempNode.alias,tempNode));
        }
    }
    //std::cout<< "numberOfReducedNodes is "<< reducedNodeMap.size()<< std::endl;
    return reducedNodeMap.size();
}

void findExpandedInputsOfReducedNodeMap(std::map <std::string, OCMNode> &ocmNodeMap, std::map <std::string, OCMNode> &reducedNodeMap)
{
    for (auto& itr: reducedNodeMap)
    {
        for (auto& ito: ocmNodeMap) // reseting input indexes ocmNodeMap
        {
            ito.second.clearInputIndexe();
        }
        findExpandedInputsforNode(itr.second.alias, ocmNodeMap, itr.second.alias, reducedNodeMap);
        if (itr.second.expandedNumberOfInputs > 0)
        {
            itr.second.expandedInputAliases = new std::string[itr.second.expandedNumberOfInputs];
            itr.second.expandedInputTypes   = new std::string[itr.second.expandedNumberOfInputs];
            itr.second.expandedInputNames   = new std::string[itr.second.expandedNumberOfInputs];
        }

    }

    for (auto& itr: reducedNodeMap)
    {
        for (auto& ito: ocmNodeMap) // reseting input indexes of ocmNodeMap
        {
            ito.second.clearInputIndexe();
        }

        fillExpandedInputsforNode(itr.second.alias, ocmNodeMap, itr.second.alias, reducedNodeMap);
    }
}

void findExpandedInputsforNode(std::string aliasOCM, std::map <std::string, OCMNode> &ocmNodeMap, std::string aliasRED, std::map <std::string, OCMNode> &reducedNodeMap)
{
    nodeMap::iterator itrocm = ocmNodeMap.find(aliasOCM);
    nodeMap::iterator itrred = reducedNodeMap.find(aliasRED);
    //std::cout<<std::endl;
    //std::cout<<"redalias = "<< aliasRED<< std::endl;
    //std::cout<<"ocmalias = "<< aliasOCM<< std::endl;
    //std::cout<<"numberOfInputs= "<<itrocm->second.numberOfInputs<<std::endl;

    /*for (int i = 0; i < itrocm->second.numberOfInputs; i++)
    {
        std::cout<<"inputalias "<<i<< " = " <<itrocm->second.inputAliases[i]<<std::endl;
    }*/

    if ((itrocm != ocmNodeMap.end()) && (itrred != reducedNodeMap.end()))
    {
        while (itrocm->second.inputIndex < itrocm->second.numberOfInputs)
        {

            std::string inputAlias = itrocm->second.inputAliases[itrocm->second.inputIndex];
            std::string inputType  = itrocm->second.inputTypes[itrocm->second.inputIndex];
            std::string inputName  = itrocm->second.inputNames[itrocm->second.inputIndex];
            itrocm->second.inputIndex++;
            if ( isItStopType(inputType) )
            {
                itrred->second.expandedNumberOfInputs++;
                //std::cout<<"expandedNumberOfInputs "<<itrred->second.expandedNumberOfInputs<<std::endl;

            }
            else /*if ( isItShadowType(inputType) )*/
            {
                findExpandedInputsforNode(inputAlias, ocmNodeMap, aliasRED, reducedNodeMap);
            }
        }
    }
    else
    {
        //std::cout<<"end"<<std::endl;
    }

}

void fillExpandedInputsforNode(std::string aliasOCM, std::map <std::string, OCMNode> &ocmNodeMap, std::string aliasRED, std::map <std::string, OCMNode> &reducedNodeMap)
{
    nodeMap::iterator itrocm = ocmNodeMap.find(aliasOCM);
    nodeMap::iterator itrred = reducedNodeMap.find(aliasRED);
    //std::cout<<"ocmalias = "<< aliasOCM<< std::endl;
    //std::cout<<"redalias = "<< aliasRED<< std::endl << std::endl;

    if ((itrocm != ocmNodeMap.end()) && (itrred != reducedNodeMap.end()))
    {
        while ( itrocm->second.inputIndex < itrocm->second.numberOfInputs)
        {
            std::string inputAlias = itrocm->second.inputAliases[itrocm->second.inputIndex];
            std::string inputType  = itrocm->second.inputTypes[itrocm->second.inputIndex];
            std::string inputName  = itrocm->second.inputNames[itrocm->second.inputIndex];
            itrocm->second.inputIndex++;
            if ( isItStopType(inputType) )
            {
                itrred->second.expandedInputAliases[itrred->second.expandedInputIndex] = inputAlias;
                itrred->second.expandedInputNames[itrred->second.expandedInputIndex]   = inputName;
                itrred->second.expandedInputTypes[itrred->second.expandedInputIndex]   = inputType;
                itrred->second.expandedInputIndex++;

            }
            else /*if ( isItShadowType(inputType) )*/
            {
                fillExpandedInputsforNode(inputAlias, ocmNodeMap, aliasRED, reducedNodeMap);
            }
        }
    }
    //std::cout<<"end"<<std::endl;
}


bool isItMainType(std::string type)
{
    if ((type == "port") || (type == "mul") || (type == "add") ||
        (type == "sub") || (type == "memory_controller") || (type == "reg"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isItStopType(std::string type)
{
    if ((type == "port") || (type == "mul") || (type == "add") ||
        (type == "sub") || (type == "value") || (type == "memory_controller")
     || (type == "reg"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isItGateType(std::string type)
{
    if ((type == "and") || (type == "or") || (type == "xor") ||
        (type == "not") ||
        (type == "nand") || (type == "nor") || (type == "xnor"))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool isItShadowType(std::string type)
{
    return true;
    if ((type == "reg") || (type == "mux") || (type == "wire"))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void findPort(std::string line, OCMNode &tempNode)
{
    std::size_t pos1, pos2;

    pos1 = line.rfind(" A");
    if (pos1 < 10000)
    {
        pos1 = line.rfind(">",pos1-1);
        pos2 = line.rfind("<",pos1-1);
        tempNode.portA = line.substr(pos2+1,pos1-pos2-1);
        tempNode.itHasPort = true;
    }

    pos1 = line.rfind(" B");
    if (pos1 < 10000)
    {
        pos1 = line.rfind(">",pos1-1);
        pos2 = line.rfind("<",pos1-1);
        tempNode.portB = line.substr(pos2+1,pos1-pos2-1);
        tempNode.itHasPort = true;
    }

    pos1 = line.rfind(" S");
    if (pos1 < 10000)
    {
        pos1 = line.rfind(">",pos1-1);
        pos2 = line.rfind("<",pos1-1);
        tempNode.portS = line.substr(pos2+1,pos1-pos2-1);
        tempNode.itHasPort = true;
    }

    pos1 = line.rfind(" D");
    if (pos1 < 10000)
    {
        pos1 = line.rfind(">",pos1-1);
        pos2 = line.rfind("<",pos1-1);
        tempNode.portD = line.substr(pos2+1,pos1-pos2-1);
        tempNode.itHasPort = true;
    }

    pos1 = line.rfind(" CLK");
    if (pos1 < 10000)
    {
        pos1 = line.rfind(">",pos1-1);
        pos2 = line.rfind("<",pos1-1);
        tempNode.portCLK = line.substr(pos2+1,pos1-pos2-1);
        tempNode.itHasPort = true;
    }
}

bool isItDataConnection(std::string line, std::string childNodeAlias, nodeMap &ocmNodeMap)
{
    nodeMap::iterator itr = ocmNodeMap.find(childNodeAlias);
    if (itr != ocmNodeMap.end())
    {
        if ((itr->second.type == "mux") || ( itr->second.type == "dff"))
        {
            std::size_t posArrow = line.find("->");
            std::size_t firtTwoDot = line.find(":", posArrow+1);
            std::size_t secondTwoDot = line.find(":", firtTwoDot+1);
            if(secondTwoDot < 10000)
            {
                std::string portName = line.substr(firtTwoDot+1, secondTwoDot-firtTwoDot-1);

                if ((portName == itr->second.portA) || (portName == itr->second.portB) ||
                        (portName == itr->second.portD))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }

        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}
