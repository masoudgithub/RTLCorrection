#include "genOCM.h"
#include <string>
#include <fstream>

int returnNumberOfNodes (const char *fileName)
{
    string line;
    ifstream schematicFile (fileName);
    int nodeCounter = 0;

    if (schematicFile.is_open())
    {
        cout<<"schematicFile file is open for the first time"<<endl;
        while (getline (schematicFile,line))
        {
            // if there is a connecction sign "->" it is not a node declaration line.
            if(line.find("->",0) > 10000)
            {
               nodeCounter++;
            }
        }
    }
    else
    {
        std::cout<<"Error: There is no "<<fileName<<" in current directory!";
    }

    schematicFile.close();
    return nodeCounter;
}

void fillRowNodes(const char *fileName, OCMNode *rowNodes,int numberOfNodes)
{

    string line;
    ifstream schematicFile (fileName);
    int nodeCounter = 0;

    if (schematicFile.is_open())
    {
        cout<<"schematicFile file is open for the first time"<<endl;
        while (getline (schematicFile,line))
        {
            if(line.find("->",0) > 10000)
            {
                // find alias
                std::size_t pos1 = 0;
                std::size_t pos2 = line.find(" ");
                rowNodes[nodeCounter].alias = line.substr(pos1,pos2-pos1);
                std::cout<<"rowNodes[node].alias = "<<rowNodes[nodeCounter].alias<<std::endl;
                // find name
                pos1 = line.find("\"",0);
                pos2 = line.find("\"",pos1+1);
                if ((pos1 < 1000) && (pos2 < 1000))
                {
                    rowNodes[nodeCounter].name = line.substr(pos1+1,pos2-pos1-1);
                }
                else
                {
                    rowNodes[nodeCounter].name = "";
                }
                std::cout<<"rowNodes[node].name = "<<rowNodes[nodeCounter].name<<std::endl;

                // find type
                if (rowNodes[nodeCounter].name.find("$add") < 1000)
                {
                    rowNodes[nodeCounter].type = "add";
                }
                else if (rowNodes[nodeCounter].name.find("$mul") < 1000)
                {
                    rowNodes[nodeCounter].type = "mul";
                }
                else if (rowNodes[nodeCounter].name.find("$sub") < 1000)
                {
                    rowNodes[nodeCounter].type = "sub";
                }
                else if (rowNodes[nodeCounter].name.find("reg") < 1000)
                {
                    rowNodes[nodeCounter].type = "reg";
                }
                else if (rowNodes[nodeCounter].name.find("$dff") < 1000)
                {
                    rowNodes[nodeCounter].type = "dff";
                }
                else if (rowNodes[nodeCounter].name.find("$pmux") < 1000)
                {
                    rowNodes[nodeCounter].type = "pmux";
                }
                else if (rowNodes[nodeCounter].name.find("$mux") < 1000)
                {
                    rowNodes[nodeCounter].type = "mux";
                }
                else if (rowNodes[nodeCounter].name.find("$and") < 1000)
                {
                    rowNodes[nodeCounter].type = "and";
                }
                else if (rowNodes[nodeCounter].name.find("$not") < 1000)
                {
                    rowNodes[nodeCounter].type = "not";
                }
                else if (rowNodes[nodeCounter].name.find("$reduce_or") < 1000)
                {
                    rowNodes[nodeCounter].type = "reduce_or";
                }
                else if (rowNodes[nodeCounter].name.find("$or") < 1000)
                {
                    rowNodes[nodeCounter].type = "or";
                }
                else if (rowNodes[nodeCounter].name.find("$eq") < 1000)
                {
                    rowNodes[nodeCounter].type = "eq";
                }
                else if (rowNodes[nodeCounter].name.find("BUF") < 1000)
                {
                    rowNodes[nodeCounter].type = "BUF";
                }
                else if (line.find("shape=octagon") < 1000)
                {
                    rowNodes[nodeCounter].type = "port";
                }
                else if ((rowNodes[nodeCounter].name.find("_bit") < 1000) && (rowNodes[nodeCounter].type != "reg"))
                {
                    rowNodes[nodeCounter].type = "wire";
                }
                else
                {
                    rowNodes[nodeCounter].type = "NON";
                }
                //
                std::cout<<"rowNodes[node].type = "<<rowNodes[nodeCounter].type<<"\n\n";
                nodeCounter++;
            }
        }
    }

}
