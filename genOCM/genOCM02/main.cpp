#include <iostream>
#include "genOCM.h"

int main()
{
    nodeMap ocmNodeMap;
    std::string dotFileName = "yosys.dot";
    fillOCMRowNodes(dotFileName.c_str(), ocmNodeMap);
    findConnections(dotFileName.c_str(), ocmNodeMap);

   /* for (auto& it: ocmNodeMap)
    {
        std::cout<<"alias= "<<it.first<<"\n";
        std::cout<<"name = "<<it.second.name<<std::endl;
        std::cout<<"type = "<<it.second.type<<std::endl;
        std::cout<<"numInputs = "<<it.second.numberOfInputs<<std::endl;
        for (int i = 0; i < it.second.numberOfInputs; i++)
        {
            std::cout<<"Type "<<i<<" = "<<it.second.inputTypes[i]<<std::endl;
            std::cout<<"Alias "<<i<<" = "<<it.second.inputAliases[i]<<std::endl;
            std::cout<<"Input "<<i<<" = "<<it.second.inputNames[i]<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"numExtInputs = "<<it.second.expandedNumberOfInputs<<std::endl<<std::endl;
        for (int i = 0; i < it.second.expandedNumberOfInputs; i++)
        {
            std::cout<<"Type "<<i<<" = "<<it.second.expandedInputTypes[i]<<std::endl;
            std::cout<<"Alias "<<i<<" = "<<it.second.expandedInputAliases[i]<<std::endl;
            std::cout<<"Input "<<i<<" = "<<it.second.expandedInputNames[i]<<std::endl;
        }
        std::cout<<std::endl;
    }
    return 0;*/
    nodeMap reducedNodeMap;
    returnNumberOfreducedNodes(ocmNodeMap, reducedNodeMap);
    findExpandedInputsOfReducedNodeMap(ocmNodeMap, reducedNodeMap);
    for (auto& it: reducedNodeMap)
    {
        it.second.clearInputIndexe();
        std::cout<<"********************************************************************************\n";
        std::cout<<"Node Alias= "<<it.first<<"\n";
        std::cout<<"Node Name = "<<it.second.name<<std::endl;
        std::cout<<"Node Type = "<<it.second.type<<std::endl<<std::endl;
        std::cout<<"Node numInputs = "<<it.second.numberOfInputs<<std::endl;
        for (int i = 0; i < it.second.numberOfInputs; i++)
        {
            std::cout<<"Input Alias"<<i<<" = "<<it.second.inputAliases[i]<<std::endl;
            std::cout<<"Input Name "<<i<<" = "<<it.second.inputNames[i]<<std::endl;
            std::cout<<"Input Type "<<i<<" = "<<it.second.inputTypes[i]<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"Node numExtInputs = "<<it.second.expandedNumberOfInputs<<std::endl;
        for (int i = 0; i < it.second.expandedNumberOfInputs; i++)
        {
            std::cout<<"Extended Input Alias "<<i<<" = "<<it.second.expandedInputAliases[i]<<std::endl;
            std::cout<<"Extended Input Name  "<<i<<" = "<<it.second.expandedInputNames[i]<<std::endl;
            std::cout<<"Extended Input Type  "<<i<<" = "<<it.second.expandedInputTypes[i]<<std::endl;
        }
        std::cout<<"##################################################################################\n";
    }
    return 0;
}
