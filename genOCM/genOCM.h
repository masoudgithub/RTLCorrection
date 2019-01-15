#ifndef GENOCM_H
#define GENOCM_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include "mainNode.h"

class genOCM : public mainNode {
public:
    typedef std::map<std::string,mainNode> nodeMap;
    typedef nodeMap::iterator nMapIt;

    nodeMap IRNodeMap;
    nodeMap IRreducedNodeMap;
    nodeMap ocmNodeMap;
    nodeMap ocmReducedNodeMap;
    std::map <std::string,int> NumberOfavailableFus;

    void fillOCMRowNodes(const char *fileName, nodeMap &ocmNodeMap, std::string moduleName);
    void fillIRRowNodes(const char *fileName, nodeMap &IRNodeMap);
    void findConnections(const char *fileName, nodeMap &ocmNodeMap);
    void fillInOutType(nodeMap &ocmNodeMap);
    int returnNumberOfreducedNodes(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap);
    void findExpandedInputsOfReducedNodeMap(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap);
    void findExpandedInputsNumforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap);
    void fillExpandedInputsforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap);
    bool isItDataConnection(std::string line, std::string childNodeAlias, nodeMap &ocmNodeMap);
    bool isOperation(std::string line);
    bool fillTempNodes(mainNode &tempNode1, mainNode &tempNode2, std::string line);
    void fillGetelemData(mainNode &tempNode2, std::string line);
    void fillGetphiData(mainNode &tempNode2, std::string line);
    void fillGetloadData(mainNode &tempNode2, std::string line);
    void fillotherOprData(mainNode &tempNode2, std::string line);
    void fillEmptyAliases(nodeMap &IRNodeMap);
    void findAndReplaceDuplicatedNodes(nodeMap &ocmNodeMap);
    void showNodeMap (nodeMap &showNodeMap, const char* name);
    void supportHierarchy(nodeMap &ocmNodeMap);
    int retDissimilarity( nMapIt IRIt, nMapIt ocmIt);
    void findInstrAlias(std::string name, std::string type, nodeMap &IRNodeMap, std::string &instrAlisa);
    void assignNumberedNames(nodeMap &ocmReducedNodeMap);
    int generate_OCM(void);

private:
    bool notExistIn(std::vector<std::string> &AlreadyAddedNodes, std::string nodeAlias);
    bool isItMainType(std::string type);
    bool isItStopType(std::string type);
    bool isItGateType(std::string type);
    bool isItShadowType(std::string type);
    void findPort(std::string line, mainNode &tempNode);
    int returnInputWidth(std::string name);
    void fillInputWidth(nodeMap &ocmNodeMap);
    void fillTypeComplete(nodeMap &ocmNodeMap);

};
#endif /*GENOCM_H*/
