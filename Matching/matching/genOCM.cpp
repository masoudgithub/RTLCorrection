#include "genOCM.h"
#include <string>
#include <fstream>
#include <regex>
#include "Hungarian.h"
#include <vector>
#include <cstdlib>

void genOCM::fillOCMRowNodes(const char *fileName, nodeMap &ocmNodeMap, std::string moduleName)
{

    std::string line;
    std::ifstream schematicFile (fileName);

    if (schematicFile.is_open())
    {
        std::cout<<"schematicFile file is open for the first time in fillRowNodes"<<std::endl;
        while (getline (schematicFile,line))
        {
            mainNode tempNode;
            tempNode.moduleName = moduleName;
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
                if ((pos1 < 10000) && (pos2 < 10000))
                {
                    tempNode.name = line.substr(pos1+1,pos2-pos1-1);
                }
                else
                {
                    tempNode.name = "";
                }
                //std::cout<<"rowNodes[node].name = "<<tempNode.name<<std::endl;

                // find type
                if (tempNode.name.find("$add") < 10000)
                {
                    tempNode.type = "add";
                }
                else if (tempNode.name.find("ram_dual_port") < 10000)
                {
                    tempNode.type = "mem_dual_port";
                }
                else if (tempNode.name.find("rom_dual_port") < 10000)
                {
                    tempNode.type = "mem_dual_port";
                }
                else if (tempNode.name.find("memory_controller") < 10000)
                {
                    tempNode.type = "shadow_port";
                }
                else if (tempNode.name.find("$mul") < 10000)
                {
                    tempNode.type = "mul";
                }
                else if (tempNode.name.find("$sub") < 10000)
                {
                    tempNode.type = "sub";
                }
                else if (tempNode.name.find("reg") < 10000)
                {
                    tempNode.type = "reg";
                    tempNode.inputWidth = returnInputWidth(tempNode.name);
                }
                else if (tempNode.name.find("$dff") < 10000)
                {
                    tempNode.type = "dff";
                }
                else if (tempNode.name.find("$pmux") < 10000)
                {
                    tempNode.type = "pmux";
                }
                else if (tempNode.name.find("$mux") < 10000)
                {
                    tempNode.type = "mux";
                }
                else if (tempNode.name.find("$and") < 10000)
                {
                    tempNode.type = "and";
                }
                else if (tempNode.name.find("$not") < 10000)
                {
                    tempNode.type = "not";
                }
                else if (tempNode.name.find("$reduce_or") < 10000)
                {
                    tempNode.type = "reduce_or";
                }
                else if (tempNode.name.find("$or") < 10000)
                {
                    tempNode.type = "or";
                }
                else if (tempNode.name.find("$eq") < 10000)
                {
                    tempNode.type = "eq";
                }
                else if (tempNode.name.find("BUF") < 10000)
                {
                    tempNode.type = "BUF";
                }
                else if (line.find("shape=octagon") < 10000)
                {
                    tempNode.type = "port";
                }
                else if ((tempNode.name.find("_bit") < 10000) && (tempNode.type != "reg"))
                {
                    tempNode.type = "wire";
                    tempNode.inputWidth = returnInputWidth(tempNode.name);
                }
                else if ((tempNode.name.find("<s") < 10000))
                {
                    tempNode.type = "wire";
                }
                else if ((tempNode.alias.find("v") < 10000))
                {
                    tempNode.type = "value";
                }
                else if (tempNode.name.find("clk") < 10000)
                {
                    tempNode.type = "clkPort";
                }
                else
                {  
                    tempNode.type = "NON";
                }
                //finding ports A, B, D, S, CLK
                findPort(line,tempNode);
                ocmNodeMap.insert(std::pair<std::string,mainNode>(tempNode.alias,tempNode));
            }
        }
        schematicFile.close();
    }
    else
    {
        std::cout<<"Error: there is no " <<fileName<<" file."<<std::endl;
    }
}


void genOCM::fillIRRowNodes(const char *fileName, nodeMap &IRNodeMap)
{

    std::string line;
    std::ifstream IRFile (fileName);
    int nodeID = 0;
        if (IRFile.is_open())
        {
            std::cout<<"schematicFile file is open for the first time in fillRowNodes"<<std::endl;
            while (getline (IRFile,line))
            {
                mainNode tempNode1;
                mainNode tempNode2;
                if(line.find(" store ",0) < 10000)
                {
                    tempNode1.alias = line.substr(2,line.size()-2);
                    tempNode1.type = "mem_dual_port";
                    tempNode1.name = line.substr(2,line.size()-2);
                    tempNode1.numberOfInputs = 2;
                    tempNode1.inputAliases = new std::string[2];
                    tempNode1.inputNames = new std::string[2];
                    tempNode1.inputTypes = new std::string[2];

                    std::size_t posSpace1 = line.find(" store ");
                    std::size_t posSpace2 = line.find(" ", posSpace1 +1);
                    std::size_t posSpace3 = line.find(" ", posSpace2 +1);
                    std::string tempString = line.substr(posSpace2+2, posSpace3-posSpace2-2);
                    tempNode1.inputWidth = std::stoi(tempString);

                    std::size_t posCommaSpace1 = line.find(", ", posSpace3 +1);
                    tempString = line.substr(posSpace3+1,posCommaSpace1-posSpace3-1);
                    tempNode1.inputAliases[0] = tempString;
                    tempNode1.inputNames[0]   = tempString;
                    if (tempString.find("%") < 1000)
                    {
                        tempNode1.inputTypes[0] = "reg";
                    }
                    else
                    {
                        tempNode1.inputTypes[0] = "value";
                    }
                    std::size_t posSpace4 = line.find(" ", posCommaSpace1 +2);
                    std::size_t posCommaSpace2 = line.find(", ", posSpace4 +1);
                    tempString = line.substr(posSpace4+1,posCommaSpace2-posSpace4-1);
                    tempNode1.inputAliases[1] = tempString;
                    tempNode1.inputNames[1]   = tempString;
                    if (tempString.find("%") < 1000)
                    {
                        tempNode1.inputTypes[1] = "reg";
                    }
                    else
                    {
                        tempNode1.inputTypes[1] = "value";
                    }
                    IRNodeMap.insert(std::pair<std::string,mainNode>(tempNode1.alias,tempNode1));
                    nodeID++;
                }
                else if ( isOperation(line) )
                {
                    if (fillTempNodes(tempNode1,tempNode2,line))
                    {
                        tempNode1.numberOfInputs = 1;
                        tempNode1.inputAliases = new std::string[1];
                        tempNode1.inputNames = new std::string[1];
                        tempNode1.inputTypes = new std::string[1];
                        tempNode1.inputAliases[0] = tempNode2.alias;
                        tempNode1.inputNames[0]   = tempNode2.name;
                        tempNode1.inputTypes[0]   = tempNode2.type;
                        IRNodeMap.insert(std::pair<std::string,mainNode>(tempNode1.alias,tempNode1));
                        IRNodeMap.insert(std::pair<std::string,mainNode>(tempNode2.alias,tempNode2));
                        nodeID += 2;
                    }
                }
            }
        }
        else
        {
            std::cout <<"Error: there is no "<<fileName<<" file."<<std::endl;
        }
}

void genOCM::findConnections(const char *fileName, nodeMap &ocmNodeMap)
{
    std::string line;
    std::ifstream schematicFile;
    mainNode tempNode;
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
                nMapIt it = ocmNodeMap.find(childNodeAlias);
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
    else
    {
        std::cout<<"Error: there is no " <<fileName<<" file."<<std::endl;
    }
    schematicFile.close();

// creating input names aliases
    for (auto& it: ocmNodeMap)
    {
        it.second.numberOfInputs++; // plus 1 for further input extraction due to hierarchy support
        it.second.inputAliases = new std::string[it.second.numberOfInputs];
        it.second.inputNames   = new std::string[it.second.numberOfInputs];
        it.second.inputTypes   = new std::string[it.second.numberOfInputs];
    }

// filling the inputs and aliases during the second pass
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
                nMapIt it = ocmNodeMap.find(childNodeAlias);
                if (it != ocmNodeMap.end())
                {
                    tempNode = it->second;
                    nMapIt pit = ocmNodeMap.find(parentNodeAlias);
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

    /*for (auto& it: ocmNodeMap)
    {
        std::cout<<"alias= "<<it.first<<"\n";
        std::cout<<"name = "<<it.second.name<<std::endl;
        std::cout<<"type = "<<it.second.type<<std::endl;
        std::cout<<"numInputs = "<<it.second.numberOfInputs<<std::endl<<std::endl;
        for ( int i = 0; i < it.second.numberOfInputs; i++)
        {
            std::cout<<"inputAlias "<<i<<" = "<<it.second.inputAliases[i]<<std::endl;
            std::cout<<"inputName  "<<i<<" = "<<it.second.inputNames[i]<<std::endl;
            std::cout<<"inputType  "<<i<<" = "<<it.second.inputTypes[i]<<std::endl<<std::endl;
        }
        std::cout<<std::endl;
    }*/
}

int genOCM::returnNumberOfreducedNodes(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap)
{
    mainNode tempNode;

    for (auto& n: ocmNodeMap)
    {
        if( isItMainType(n.second.type))
        {
            tempNode = n.second;
            reducedNodeMap.insert(std::pair<std::string, mainNode>(tempNode.alias,tempNode));
        }
    }
    //std::cout<< "numberOfReducedNodes is "<< reducedNodeMap.size()<< std::endl;
    return reducedNodeMap.size();
}

void genOCM::findExpandedInputsOfReducedNodeMap(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap)
{
    for (auto& itr: reducedNodeMap)
    {
        for (auto& ito: ocmNodeMap) // reseting input indexes ocmNodeMap
        {
            ito.second.clearInputIndexe();
        }
        findExpandedInputsNumforNode(itr.second.alias, ocmNodeMap, itr.second.alias, reducedNodeMap);
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

void genOCM::findExpandedInputsNumforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap)
{
    nMapIt itrocm = ocmNodeMap.find(aliasOCM);
    nMapIt itrred = reducedNodeMap.find(aliasRED);
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
                findExpandedInputsNumforNode(inputAlias, ocmNodeMap, aliasRED, reducedNodeMap);
            }
        }
    }
    else
    {
        //std::cout<<"end"<<std::endl;
    }

}

void genOCM::fillExpandedInputsforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap)
{
    nMapIt itrocm = ocmNodeMap.find(aliasOCM);
    nMapIt itrred = reducedNodeMap.find(aliasRED);
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


bool genOCM::isItMainType(std::string type)
{
    if ((type == "port") || (type == "mul") || (type == "add") ||
        (type == "sub")  || (type == "reg") ||
        (type == "mem_dual_port"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool genOCM::isItStopType(std::string type)
{
    if ((type == "port") || (type == "mul") || (type == "add") ||
        (type == "sub") || (type == "value") ||
        (type == "mem_dual_port") || (type == "reg"))
     /*|| (type == "reg"))*/
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool genOCM::isItGateType(std::string type)
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


bool genOCM::isItShadowType(std::string type)
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
void genOCM::findPort(std::string line, mainNode &tempNode)
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

bool genOCM::isItDataConnection(std::string line, std::string childNodeAlias, nodeMap &ocmNodeMap)
{
    nMapIt itr = ocmNodeMap.find(childNodeAlias);
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
bool genOCM::isOperation(std::string line)
{
    if (line.find(" = ") < 10000)
    {
        if ( (line.find(" mul ") < 1000) || (line.find(" add ") < 1000)  ||
             (line.find(" sub ") < 1000) || (line.find(" icmp ") < 1000) ||
             (line.find(" phi ") < 1000) || (line.find(" load ") < 1000) ||
             (line.find(" getelementptr ") < 1000) )
        {
            return true;
        }
    }
    return false;
}

bool genOCM::fillTempNodes(mainNode &tempNode1, mainNode &tempNode2, std::string line)
{
    if ( (line.find (" sub ") < 10000) || (line.find(" add ") < 1000) ||
         (line.find (" mul ") < 10000) || (line.find(" load ") < 1000) ||
         (line.find (" icmp ") < 10000) || (line.find (" phi ") < 10000) ||
         (line.find(" getelementptr ") < 1000))
    {
        std::size_t posEqual = line.find(" = ");
        std::size_t posSpace1 = line.rfind(" ", posEqual-1);
        std::size_t posSpace2 = posEqual+2;
        std::size_t posSpace3 = line.find(" ",posSpace2+1);
        std::string tempString = line.substr(posSpace2+1, posSpace3- posSpace2 -1);
        tempNode2.type = tempString;
        tempNode2.name = line.substr(2,line.size()-2);;
        tempNode2.alias = line.substr(2,line.size()-2);;
        if (tempNode2.type == "getelementptr")
        {
            fillGetelemData(tempNode2, line);
        }
        else if (tempNode2.type == "phi")
        {
            fillGetphiData(tempNode2, line);
        }
        else if (tempNode2.type == "load")
        {
            tempNode2.type = "mem_dual_port";
            fillGetloadData(tempNode2, line);
        }
        else
        {
            fillotherOprData(tempNode2, line);
        }

        tempString = line.substr(posSpace1+1,posEqual-posSpace1-1);
        if (tempString.find("%") < 10000)
        {
            tempNode1.type = "reg";
            tempNode1.name = line.substr(2,line.size()-2);;
            tempNode1.alias = tempString;
        }
        return true;
    }
    return false;
}

void genOCM::fillGetelemData(mainNode &tempNode2, std::string line)
{
    tempNode2.numberOfInputs = 3;
    tempNode2.inputAliases = new std::string[3];
    tempNode2.inputTypes = new std::string[3];
    tempNode2.inputNames = new std::string[3];
    tempNode2.inputNames = new std::string[3];

    std::size_t starSpace = line.find("* ");
    std::size_t commaSpace1 = line.find(", ",starSpace+1);
    std::string tempString = line.substr(starSpace+2, commaSpace1-starSpace-2);
    tempNode2.inputNames[0] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[0] = tempString;
        tempNode2.inputTypes[0] = "reg";
    }
    else
    {
        tempNode2.inputAliases[0] = "NON";
        tempNode2.inputTypes[0] = "value";
    }

    std::size_t midSpace = line.find(" ",commaSpace1+2);
    std::size_t commaSpace2 = line.find(", ",midSpace+1);
    tempString = line.substr(midSpace+1, commaSpace2-midSpace-1);
    tempNode2.inputNames[1] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[1] = tempString;
        tempNode2.inputTypes[1] = "reg";
    }
    else
    {
        tempNode2.inputAliases[1] = "NON";
        tempNode2.inputTypes[1] = "value";
    }

    midSpace = line.find(" ",commaSpace2+2);
    std::size_t lineLength = line.length();
    tempString = line.substr(midSpace+1, lineLength-midSpace-1);
    tempNode2.inputNames[2] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[2] = tempString;
        tempNode2.inputTypes[2] = "reg";
    }
    else
    {
        tempNode2.inputAliases[2] = "NON";
        tempNode2.inputTypes[2] = "value";
    }
}

void genOCM::fillGetphiData(mainNode &tempNode2, std::string line)
{
    tempNode2.numberOfInputs = 2;
    tempNode2.inputAliases = new std::string[2];
    tempNode2.inputTypes = new std::string[2];
    tempNode2.inputNames = new std::string[2];
    tempNode2.inputNames = new std::string[2];

    std::size_t brakSpace1 = line.find("[ ");
    std::size_t commaSpace1 = line.find(", ",brakSpace1+1);
    std::string tempString = line.substr(brakSpace1+2, commaSpace1-brakSpace1-2);
    tempNode2.inputNames[0] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[0] = tempString;
        tempNode2.inputTypes[0] = "reg";
    }
    else
    {
        tempNode2.inputAliases[0] = "NON";
        tempNode2.inputTypes[0] = "value";
    }

    std::size_t brakSpace2 = line.find("[ ",commaSpace1+2);
    std::size_t commaSpace2 = line.find(", ",brakSpace2+1);
    tempString = line.substr(brakSpace2+2, commaSpace2-brakSpace2-2);
    tempNode2.inputNames[1] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[1] = tempString;
        tempNode2.inputTypes[1] = "reg";
    }
    else
    {
        tempNode2.inputAliases[1] = "NON";
        tempNode2.inputTypes[1] = "value";
    }
}

void genOCM::fillGetloadData(mainNode &tempNode2, std::string line)
{

    tempNode2.numberOfInputs = 1;
    tempNode2.inputAliases = new std::string[1];
    tempNode2.inputTypes = new std::string[1];
    tempNode2.inputNames = new std::string[1];
    tempNode2.inputNames = new std::string[1];

    std::size_t starSpace1 = line.find("* ");
    std::size_t commaSpace1 = line.find(", ",starSpace1+1);
    std::string tempString = line.substr(starSpace1+2, commaSpace1-starSpace1-2);
    tempNode2.inputNames[0] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[0] = tempString;
        tempNode2.inputTypes[0] = "reg";
    }
    else
    {
        tempNode2.inputAliases[0] = "NON";
        tempNode2.inputTypes[0] = "value";
    }
}
void genOCM::fillotherOprData(mainNode &tempNode2, std::string line)
{
    tempNode2.numberOfInputs = 2;
    tempNode2.inputAliases = new std::string[2];
    tempNode2.inputTypes = new std::string[2];
    tempNode2.inputNames = new std::string[2];
    tempNode2.inputNames = new std::string[2];

    std::size_t commaSpace1 = line.find(", ");
    std::size_t Space1 = line.rfind(" ",commaSpace1);
    std::string tempString = line.substr(Space1+1, commaSpace1-Space1-1);
    tempNode2.inputNames[0] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[0] = tempString;
        tempNode2.inputTypes[0] = "reg";
    }
    else
    {
        tempNode2.inputAliases[0] = "NON";
        tempNode2.inputTypes[0] = "value";
    }

    std::size_t lineEnd = line.length();
    tempString = line.substr(commaSpace1+2, lineEnd-commaSpace1-2);
    tempNode2.inputNames[1] = tempString;
    if( tempString.find("%") < 10000)
    {
        tempNode2.inputAliases[1] = tempString;
        tempNode2.inputTypes[1] = "reg";
    }
    else
    {
        tempNode2.inputAliases[1] = "NON";
        tempNode2.inputTypes[1] = "value";
    }

}

void genOCM::fillEmptyAliases(nodeMap &IRNodeMap)
{
    int aliasNum = 0;

    for (auto& it: IRNodeMap)
    {
        if (it.second.alias == "NON")
        {
            it.second.alias = "NON"+ std::to_string(aliasNum);
            aliasNum++;
        }

        for (int i = 0; i < it.second.numberOfInputs; i++)
        {
            if (it.second.inputAliases[i] == "NON")
            {
                it.second.inputAliases[i] = "NON"+ std::to_string(aliasNum);
                aliasNum++;
            }
        }
    }
}

bool genOCM::notExistIn(std::vector<std::string> &AlreadyAddedNodes, std::string nodeAlias)
{
    if ( std::find(AlreadyAddedNodes.begin(), AlreadyAddedNodes.end(), nodeAlias) != AlreadyAddedNodes.end() )
       return false;
    else
       return true;
}

void genOCM::findAndReplaceDuplicatedNodes(nodeMap &ocmNodeMap)
{
    // findind duplicated nodes
    int flag, c1 = 0, c2 = 0;
    std::map<std::string, std::vector <std::string>> aliasMap;
    std::vector <std::string> dupNodeList;

    for (auto& i: ocmNodeMap)
    {
        flag = 0;
        std::vector <std::string> temp;

        for (auto& j:ocmNodeMap)
        {
            if ((i.first != j.first) && (i.second.name == j.second.name)
                && ((i.second.type =="port") || (i.second.type =="shadow_port"))
                && notExistIn(dupNodeList, j.first))
            {
                flag =1;
                temp.push_back(j.first);
               /* std::cout<<i.first<<" "<<i.second.name<<" dup "<<j.first<<" "<<j.second.name<<std::endl;*/
            }
        }
        if (flag)
        {
            c1++;
            //temp.push_back(i.first);
            dupNodeList.push_back(i.first);
            /*for (auto& k: temp)
            {
                std::cout<< k <<" ";
            }
            std::cout<<std::endl;*/
            aliasMap.insert(std::pair<std::string, std::vector <std::string>>(i.first,temp));
        }
    }
    // replaceing duplicated aliases

    for (auto& a: aliasMap)
    {
        for (auto& k: a.second)
        {
            for (auto& o: ocmNodeMap)
            {
                for (int in = 0; in < o.second.numberOfInputs; in++)
                {
                    if (o.second.inputAliases[in] == k)// replace the duplicated by main one
                    {
                        std::string str1 = o.second.inputAliases[in];
                       /* std::cout<<"in "<< in<<" before replace= "<<str1<<std::endl;*/
                        o.second.inputAliases[in] = a.first;
                        std::string str2 = o.second.inputAliases[in];
                        /*std::cout<<"after replace= "<<str2<<std::endl;*/
                        c2++;
                    }
                }
            }
        }
    }
    //
   /* std::cout<<"c1 = "<<c1<<std::endl;
    std::cout<<"c2 = "<<c2<<std::endl;*/

    for (auto& a: aliasMap) // removing duplicated nodes
    {
        for (auto& k: a.second)
        {
            ocmNodeMap.erase(k);
        }
    }
}

void genOCM::supportHierarchy(nodeMap &ocmNodeMap)
{
    // findind duplicated nodes
    int flag, c1 = 0, numberOfInputs;
    std::map<std::string, std::vector <std::string>> aliasMap;
    std::vector <std::string> dupNodeList;
    std::string inputAlias, outputAlias;
    for (auto& i: ocmNodeMap)
    {
        flag = 0;
        std::vector <std::string> temp;

        for (auto& j:ocmNodeMap)
        {
            if ((i.first != j.first) && (i.second.name == j.second.name)
                && ((i.second.type =="port") || (i.second.type =="shadow_port"))
                /*&& notExistIn(dupNodeList, j.first)*/
                && (j.second.moduleName != i.second.moduleName))
            {
                if ((i.second.inOutType == "in") && (j.second.inOutType == "out"))
                {
                    flag =1;
                    inputAlias = i.first;
                    outputAlias = j.first;
                    temp.push_back(j.first);
                    /*std::cout<<i.first<<" in "<<i.second.name<<" dup "<<j.first<<" out "<<j.second.name<<std::endl;*/
                    break;
                }
                else if ((i.second.inOutType == "out") && (j.second.inOutType == "in"))
                {
                    flag =1;
                    inputAlias = j.first;
                    outputAlias = i.first;
                    temp.push_back(j.first);
                    /*std::cout<<i.first<<" out "<<i.second.name<<" dup "<<j.first<<" in "<<j.second.name<<std::endl;*/
                    break;
                }

            }
        }

        if (flag)
        {
            c1++;
            //temp.push_back(i.first);
            dupNodeList.push_back(i.first);
           /* for (auto& k: temp)
            {
                std::cout<< k <<" ";
            }*/
            /*std::cout<<std::endl;*/
            aliasMap.insert(std::pair<std::string, std::vector <std::string>>(i.first,temp));
            numberOfInputs = ocmNodeMap.at(inputAlias).numberOfInputs;
            ocmNodeMap.at(inputAlias).inputAliases[numberOfInputs-1] = outputAlias;
            ocmNodeMap.at(inputAlias).inputTypes[numberOfInputs-1] = ocmNodeMap.at(outputAlias).type;
            ocmNodeMap.at(inputAlias).inputNames[numberOfInputs-1] = ocmNodeMap.at(outputAlias).name;
        }
    }
    // replaceing duplicated aliases

   /* for (auto& a: aliasMap)
    {
        for (auto& k: a.second)
        {
            //ito = ocmNodeMap.find(k);

        }
    }
    //
    std::cout<<"c1 = "<<c1<<std::endl;
    std::cout<<"c2 = "<<c2<<std::endl;

    for (auto& a: aliasMap) // removing duplicated nodes
    {
        for (auto& k: a.second)
        {
            ocmNodeMap.erase(k);
        }
    }*/
}

void genOCM::showNodeMap (nodeMap &showNodeMap, const char* name)
{
    std::ofstream logFile;
    std::string logFileName = std::string(name) + ".log";
    logFile.open(logFileName);
        for (auto& it: showNodeMap)
    {
        it.second.clearInputIndexe();
        logFile<<"**************************** "<<name<<" ***********************************************\n";
        logFile<<"Node Alias= "<<it.first<<"\n";
        logFile<<"Node Module = "<<it.second.moduleName<<std::endl;
        logFile<<"Node Name = "<<it.second.name<<std::endl;
        logFile<<"Node NumberedName = "<<it.second.nameNumbered<<std::endl;
        logFile<<"Node Type = "<<it.second.type<<std::endl<<std::endl;
        logFile<<"Node completeType = "<<it.second.typeComplete<<std::endl<<std::endl;
        logFile<<"Node inOutType = "<<it.second.inOutType<<std::endl<<std::endl;
        logFile<<"Node numInputs = "<<it.second.numberOfInputs<<std::endl;
        logFile<<"Node inputWidth = "<<it.second.inputWidth<<std::endl;
        for (int i = 0; i < it.second.numberOfInputs; i++)
        {
            logFile<<"Input Alias "<<i<<" = "<<it.second.inputAliases[i]<<std::endl;
            logFile<<"Input Name "<<i<<" = "<<it.second.inputNames[i]<<std::endl;
            logFile<<"Input Type "<<i<<" = "<<it.second.inputTypes[i]<<std::endl;
        }

        logFile<<std::endl;
        logFile<<"Node numExtInputs = "<<it.second.expandedNumberOfInputs<<std::endl;
        for (int i = 0; i < it.second.expandedNumberOfInputs; i++)
        {
            logFile<<"Extended Input Alias "<<i<<" = "<<it.second.expandedInputAliases[i]<<std::endl;
            logFile<<"Extended Input Name  "<<i<<" = "<<it.second.expandedInputNames[i]<<std::endl;
            logFile<<"Extended Input Type  "<<i<<" = "<<it.second.expandedInputTypes[i]<<std::endl;
        }
        logFile<<"##################################################################################\n";
    }
}

void genOCM::fillInOutType(nodeMap &ocmNodeMap)
{
    for(auto& o: ocmNodeMap)
    {
        if ((o.second.type == "port") || (o.second.type == "shadow_port"))
        {
            if (o.second.numberOfInputs > 1)
            {
                o.second.inOutType = "out";
            }
            else
            {
                o.second.inOutType = "in";
            }
        }
    }
}

void genOCM::findInstrAlias(std::string name, std::string type, nodeMap &IRNodeMap, std::string &instrAlisa)
{
    instrAlisa = "NULL";
    for(auto& i: IRNodeMap)
    {
        if ( (i.second.name == name) /*&& (i.second.type == type) */)
        {
            /*std::cout<<"i.second.name = "<<i.second.name<<std::endl;
            std::cout<<"         name = "<<name<<std::endl;
            std::cout<<"i.second.type = "<<i.second.type<<std::endl;
            std::cout<<"         type = "<<type<<std::endl;*/

            if (i.second.typeComplete == type)
            {
                instrAlisa = i.first;
            }
        }
    }
}

int genOCM::retDissimilarity( nMapIt IRIt, nMapIt ocmIt)
{

 /*   std::cout<< IRIt->second.type <<std::endl;*/
    if ((IRIt->second.type == "mul") && (ocmIt->second.type == "mul"))
    {
     std::cout <<ocmIt->second.type<<std::endl;
    }
    int numberOfDiffInputs = IRIt->second.expandedNumberOfInputs;
    if (IRIt->second.typeComplete == ocmIt->second.typeComplete)
    {
        for (int i = 0; i < IRIt->second.expandedNumberOfInputs; i++)
        {
            for (int j = 0; j < ocmIt->second.expandedNumberOfInputs; j++)
            {
                if  (IRIt->second.expandedInputTypes[i] == "value")
                {
                    if (IRIt->second.expandedInputTypes[i] == ocmIt->second.expandedInputTypes[j])
                    {
                        if (IRIt->second.expandedInputNames[i] == ocmIt->second.expandedInputNames[j])
                        {
                            numberOfDiffInputs--;
                            break;
                        }
                    }
                }
                else
                {
                     if (IRIt->second.expandedInputTypes[i] == ocmIt->second.expandedInputTypes[j])
                     {
                        numberOfDiffInputs--;
                        break;
                     }
                }
            }
        }
        return numberOfDiffInputs;
    }
    else
        return Not_Matched_Cost;
}

int genOCM::generate_OCM(void)
{

    int numRedNode = 0, c_numRedNode = 0;
    const char *argv[6] = {"main.dot", "memory_controller.dot", "total.dot", "c_main.dot", "c_memory_controller.dot", "c_total.dot"};
    genOCM mainGenOCM;

    std::string dotFileName;
    std::size_t pos;
    std::string moduleName;

    dotFileName = argv[0];
    pos = dotFileName.find(".");
    moduleName = dotFileName.substr(0,pos);
    fillOCMRowNodes(dotFileName.c_str(), ocmNodeMap, moduleName);
    dotFileName = argv[1];
    pos = dotFileName.find(".");
    moduleName = dotFileName.substr(0,pos);
    fillOCMRowNodes(dotFileName.c_str(), ocmNodeMap, moduleName);
    findConnections(argv[2], ocmNodeMap);
    fillInOutType(ocmNodeMap);
    fillInputWidth(ocmNodeMap);
    fillTypeComplete(ocmNodeMap);
    showNodeMap (ocmNodeMap, "OCM Node");
    //findAndReplaceDuplicatedNodes(ocmNodeMap);
    supportHierarchy(ocmNodeMap);
    showNodeMap (ocmNodeMap, "OCM dup Node");
    numRedNode = returnNumberOfreducedNodes(ocmNodeMap, ocmReducedNodeMap);
    findExpandedInputsOfReducedNodeMap(ocmNodeMap, ocmReducedNodeMap);
    assignNumberedNames(ocmReducedNodeMap);
    showNodeMap (ocmReducedNodeMap, "OCM Reduced Node");

    dotFileName = argv[3];
    pos = dotFileName.find(".");
    moduleName = dotFileName.substr(0,pos);
    fillOCMRowNodes(dotFileName.c_str(), c_ocmNodeMap, moduleName);
    dotFileName = argv[4];
    pos = dotFileName.find(".");
    moduleName = dotFileName.substr(0,pos);
    fillOCMRowNodes(dotFileName.c_str(), c_ocmNodeMap, moduleName);
    findConnections(argv[5], c_ocmNodeMap);
    fillInOutType(c_ocmNodeMap);
    fillInputWidth(c_ocmNodeMap);
    fillTypeComplete(c_ocmNodeMap);
    showNodeMap (c_ocmNodeMap, "OCM Node");
    //findAndReplaceDuplicatedNodes(ocmNodeMap);
    supportHierarchy(c_ocmNodeMap);
    showNodeMap (c_ocmNodeMap, "OCM dup Node");
    c_numRedNode = returnNumberOfreducedNodes(c_ocmNodeMap, c_ocmReducedNodeMap);
    findExpandedInputsOfReducedNodeMap(c_ocmNodeMap, c_ocmReducedNodeMap);
    assignNumberedNames(c_ocmReducedNodeMap);
    showNodeMap (c_ocmReducedNodeMap, "OCM Reduced Node");

    int max_numNode = c_numRedNode;
    if (numRedNode > c_numRedNode)
    {
        max_numNode = numRedNode;
    }

    hungarian_problem_t p;
    Table weights(max_numNode, std::vector<int>(max_numNode));
    Table assignments(max_numNode, std::vector<int>(max_numNode));
    for (int i = 0; i < max_numNode; i++)
    {
        for (int j = 0; j < max_numNode; j++)
        {
            weights[i][j] = Not_Matched_Cost;
        }
    }

    {
        int i = 0 , j = 0;
        for (nMapIt it1 = c_ocmReducedNodeMap.begin(); it1 != c_ocmReducedNodeMap.end(); it1++)
        {

            for (nMapIt it2 = ocmReducedNodeMap.begin(); it2 != ocmReducedNodeMap.end(); it2++)
            {

                weights[i][j] = retDissimilarity(it1, it2);
                j++;
            }
            j = 0;
            i++;
        }
    }

    int rows = max_numNode;
    //assert(rows > 0);
    int cols = max_numNode;
    //assert(cols > 0);

    // not necessary but good to enforce
    //assert(rows == cols);

    int** m = vector_to_matrix(weights, rows, cols);

    /* initialize the hungarian_problem using the cost matrix*/
    hungarian_init(&p, m, rows, cols,
            HUNGARIAN_MODE_MINIMIZE_COST);

    /* solve the assignement problem */
    hungarian_solve(&p);
    /*findInstrAlias(ittest1->second.name, ittest1->second.type,IRreducedNodeMap, str);
    ittest1 = IRreducedNodeMap.find(str);*/
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            assignments[i][j] = p.assignment[i][j];
        }
    }
    int matched = 0;
    int cost = 0;
    int num_notMatched = 0;

    nMapIt it1 = c_ocmReducedNodeMap.begin();
    nMapIt it2 = ocmReducedNodeMap.begin();
    std::cout<<std::endl;
    for (int i = 0; i < max_numNode; i++)
    {
        matched = 0;
        it2 = ocmReducedNodeMap.begin();
        for (int j = 0; j < max_numNode; j++) {
            if (assignments[i][j] == 1) {
                cost += weights[i][j];
                matched = 1;
                if (weights[i][j] == Not_Matched_Cost) {
                    std::cout<<it1->second.nameNumbered<< " Not Matched"<<std::endl;
                }
            }
            it2++;
        }
        it1++;
    }

    std::cout<<std::endl;
    it1 = c_ocmReducedNodeMap.begin();
    for (int i = 0; i < max_numNode; i++)
    {
        matched = 0;
        it2 = ocmReducedNodeMap.begin();
        for (int j = 0; j < max_numNode; j++) {
            if (assignments[i][j] == 1) {

                matched = 1;
                if (weights[i][j] == 0) {
                    std::cout<<it1->second.nameNumbered<< " matched to "<<it2->second.nameNumbered << " with cost \t"<<weights[i][j]<<std::endl;
                }
            }
            it2++;
        }
        it1++;
    }

    std::cout<<std::endl;
    it1 = c_ocmReducedNodeMap.begin();
    for (int i = 0; i < max_numNode; i++)
    {
        matched = 0;
        it2 = ocmReducedNodeMap.begin();
        for (int j = 0; j < max_numNode; j++) {
            if (assignments[i][j] == 1) {

                matched = 1;
                if ((weights[i][j] < Not_Matched_Cost) && (weights[i][j] > 0)) {
                    std::cout<<it1->second.nameNumbered<< " matched to "<<it2->second.nameNumbered << " with cost "<<weights[i][j]<<std::endl;
                }
            }
            it2++;
        }
        it1++;
    }

    /* free used memory */
    hungarian_free(&p);
    for(int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);


    return 0;
}

void genOCM::assignNumberedNames(nodeMap &ocmReducedNodeMap)
{
    std::string type = "";
    for (auto& n:ocmReducedNodeMap)
    {
        type = n.second.typeComplete;
        if (NumberOfavailableFus.find(type) == NumberOfavailableFus.end()) /* the fu type is not existed before*/
        {
            n.second.nameNumbered = type+"_0";
            NumberOfavailableFus.insert({type,1});
        }
        else /* the fu exists in prior*/
        {
            n.second.nameNumbered = type + "_" + std::to_string (NumberOfavailableFus.at(type));
            NumberOfavailableFus.at(type) = NumberOfavailableFus.at(type) + 1;
        }
    }
}

int genOCM::returnInputWidth(std::string name)
{
    int pos2 = name.find("_bit");
    int pos1 = name.rfind("_",pos2-1);
    std::string inputWidth = name.substr(pos1+1,pos2-pos1-1);
    return std::stoi(inputWidth);
}

void genOCM::fillInputWidth(nodeMap &ocmNodeMap)
{
    /*std::cout<<"********************************\n";*/
    int cnt = 0;
    for (auto& o:ocmNodeMap)
    {
        for (int i = 0; i < o.second.numberOfInputs; i++)
        {
            if ( (o.second.inputTypes[i] == "wire") || (o.second.inputTypes[i] == "reg"))
            {
                std::string tempAlias = o.second.inputAliases[i];
                if (ocmNodeMap.at(tempAlias).inputWidth > o.second.inputWidth)
                {
                    o.second.inputWidth = ocmNodeMap.at(tempAlias).inputWidth;
                   /* std::cout<<ocmNodeMap.at(tempAlias).inputWidth<<std::endl;*/
                    cnt++;
                }
            }
        }
    }
    if (cnt > 0)
    {
        fillInputWidth(ocmNodeMap);
    }
}

void genOCM::fillTypeComplete(nodeMap &ocmNodeMap)
{
    std::string temp;
    for (auto& o:ocmNodeMap)
    {
        temp = "";
        if(o.second.type == "add")
        {
            o.second.typeComplete = temp + "signed_" + "add_" + std::to_string(o.second.inputWidth);
        }
        else if (o.second.type == "mul")
        {
            o.second.typeComplete = temp + "signed_" + "multiply_" + std::to_string(o.second.inputWidth);
        }
        else if (o.second.type == "sub")
        {
            o.second.typeComplete = temp + "signed_" + "subtract_" + std::to_string(o.second.inputWidth);
        }
        else
        {
            o.second.typeComplete = o.second.type;
        }
    }
}

void genOCM::fillIRinputWidth(nodeMap &IRNodeMap)
{
    for (auto& o:IRNodeMap)
    {
        if(o.first.find("i8") < 10000)
        {
            o.second.inputWidth = 8;
        }
        else if (o.first.find("i16") < 10000)
        {
            o.second.inputWidth = 16;
        }
        else if (o.first.find("i32") < 10000)
        {
            o.second.inputWidth = 32;
        }
    }
}
void genOCM::fillIRTypeComplete(nodeMap &IRNodeMap)
{
    std::string temp = "";
    for (auto& o:IRNodeMap)
    {
        if (o.second.type == "mul")
        {
            o.second.typeComplete = temp + "signed_multiply_" + std::to_string(o.second.inputWidth);
        }
        else if (o.second.type == "add")
        {
            o.second.typeComplete = temp + "signed_add_" + std::to_string(o.second.inputWidth);
        }
        else if (o.second.type == "sub")
        {
            o.second.typeComplete = temp + "signed_subtract_" + std::to_string(o.second.inputWidth);
        }
        else
        {
            o.second.typeComplete = o.second.type;
        }
    }
}

int genOCM::findInstrFUmatch(std::string InstrName, std::string InstrType, std::string FUname)
{

    std::string InstrAlias;
    findInstrAlias(InstrName, InstrType, IRreducedNodeMap, InstrAlias);
   /* std::cout<<"InstrAlias 1322 = "<<InstrAlias<<std::endl;*/
    nMapIt InstrIt = IRreducedNodeMap.find(InstrAlias);
    if (InstrIt == IRreducedNodeMap.end())
    {
        std::cout<<"Instruction *"<< InstrName<<"* not found in IRreducedNodeMap"<<std::endl;
        return 100;
    }

    std::string FUalias = returnFUAlias(FUname, ocmReducedNodeMap);
    nMapIt FUIt = ocmReducedNodeMap.find(FUalias);
    if (InstrIt == ocmReducedNodeMap.end())
    {
        std::cout<<"FU *"<<FUname<<"* not found in ocmReducedNodeMap"<<std::endl;
        return 100;
    }

    int disSimValue = retDissimilarity(InstrIt, FUIt);
    //std::cout<<"disSimValue = "<<disSimValue<<std::endl;
    return disSimValue;
}

std::string genOCM::returnFUAlias(std::string FUname, nodeMap &ocmReducedNodeMap)
{
    std::string temp = "";
    for (auto& o:ocmReducedNodeMap)
    {
        if (o.second.nameNumbered == FUname)
        {
            return o.first;
        }
        temp = o.first;
    }
    return temp;
}

int** genOCM::vector_to_matrix(Table &v, int rows,
        int cols) {
    int i, j;
    int** m;
    // allocate an array of pointers (arrays)
    m = (int**)calloc(rows,sizeof(int*));
    //assert(m);
    for(i = 0; i < rows; i++) {
        // allocate an array of integers
        m[i] = (int*)calloc(cols,sizeof(int));
        //assert(m[i]);
        for(j = 0; j < cols; j++) {
            m[i][j] = v[i][j];
        }
    }
    return m;
}
