#include <iostream>
#include "genOCM.h"
#include <string>

// inputs "xx.ll" "first xx.dot" "second xx.dot" ...
int main(int argc, char *argv[])
{
    std::cout<<"argc = " << argc << std::endl;
    if (argc >= 3)
    {
        // creating IR node map
        nodeMap IRNodeMap;
        nodeMap IRreducedNodeMap;
        std::string IRFileName = argv[1];
        fillIRRowNodes(IRFileName.c_str(),IRNodeMap);
        fillEmptyAliases(IRNodeMap);
        returnNumberOfreducedNodes(IRNodeMap, IRreducedNodeMap);
        findExpandedInputsOfReducedNodeMap(IRNodeMap, IRreducedNodeMap);
        showNodeMap (IRreducedNodeMap, "IR Reduced Node");
        // creating OCM node Map
        nodeMap ocmNodeMap;
        nodeMap reducedNodeMap;
        std::string dotFileName;
        nMapIt ite;
        for (int i = 2; i < argc-1; i++)
        {
            dotFileName = argv[i];
            std::size_t pos = dotFileName.find(".");
            std::string moduleName = dotFileName.substr(0,pos);
            fillOCMRowNodes(dotFileName.c_str(), ocmNodeMap, moduleName);
            //findConnections(dotFileName.c_str(), ocmNodeMap);
        }
        findConnections(argv[argc-1], ocmNodeMap);
        fillInOutType(ocmNodeMap);
        showNodeMap (ocmNodeMap, "OCM Node");
        //findAndReplaceDuplicatedNodes(ocmNodeMap);
        supportHierarchy(ocmNodeMap);
        showNodeMap (ocmNodeMap, "OCM dup Node");
        returnNumberOfreducedNodes(ocmNodeMap, reducedNodeMap);
        findExpandedInputsOfReducedNodeMap(ocmNodeMap, reducedNodeMap);
        showNodeMap (reducedNodeMap, "OCM Reduced Node");

        std::map <std::string,int> availableFus;
        availableFus.insert({"add",2});
        availableFus.insert({"sub",1});
        availableFus.insert({"mul",1});
        availableFus.insert({"mem_dual_port",2});
        for (auto& it:availableFus)
        {
            std::cout<< "FU = "<< it.first << " num = "<<it.second<<std::endl;
        }

        nMapIt ittest1 = IRreducedNodeMap.begin();
        nMapIt ittest2 = reducedNodeMap.begin();
        std::string str;
        findInstrAlias(ittest1->second.name, ittest1->second.type,IRreducedNodeMap, str);

        ittest1 = IRreducedNodeMap.find(str);
        int mindissimi = 100;
        int dissimTemp = 100;
        while ( ittest2 != reducedNodeMap.end())
        {
            dissimTemp = retDissimilarity(ittest1, ittest2);
            if (dissimTemp < mindissimi)
            {
                mindissimi = dissimTemp;
            }
            ittest2++;
        }

        return 0;
    }
    else
    {
        return -1;
    }
}
