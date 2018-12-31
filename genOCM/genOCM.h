#ifndef GENOCM_H
#define GENOCM_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include "mainNode.h"
/*class mainNode
{
public:
    std::string inOutType = "NON";
    std::string moduleName;
    std::string alias;
    std::string name;
    std::string type;
    std::string portA;
    std::string portB;
    std::string portD;
    std::string portS;
    std::string portCLK;
    int inputWidth;
    bool itHasPort = false;
    int numberOfInputs = 0;
    int inputIndex = 0;
    std::string *inputNames;
    std::string *inputAliases;
    std::string *inputTypes;

    int expandedNumberOfInputs = 0;
    int expandedInputIndex = 0;
    std::string *expandedInputNames;
    std::string *expandedInputAliases;
    std::string *expandedInputTypes;

    void clearInputIndexe() { inputIndex = 0;}
    void clearEXPInputIndex() {expandedInputIndex = 0;}
};*/

class genOCM : public mainNode {
    public:
    typedef std::map<std::string,mainNode> nodeMap;
    typedef nodeMap::iterator nMapIt;

    nodeMap IRNodeMap;
    nodeMap IRreducedNodeMap;
    nodeMap ocmNodeMap;
    nodeMap reducedNodeMap;

    void fillOCMRowNodes(const char *fileName, nodeMap &ocmNodeMap, std::string moduleName);
    void fillIRRowNodes(const char *fileName, nodeMap &IRNodeMap);
    void findConnections(const char *fileName, nodeMap &ocmNodeMap);
    void fillInOutType(nodeMap &ocmNodeMap);
    int returnNumberOfreducedNodes(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap);
    void findExpandedInputsOfReducedNodeMap(nodeMap &ocmNodeMap, nodeMap &reducedNodeMap);
    void findExpandedInputsNumforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap);
    void fillExpandedInputsforNode(std::string aliasOCM, nodeMap &ocmNodeMap, std::string aliasRED, nodeMap &reducedNodeMap);
    bool isItMainType(std::string type);
    bool isItStopType(std::string type);
    bool isItGateType(std::string type);
    bool isItShadowType(std::string type);
    void findPort(std::string line, mainNode &tempNode);
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
    bool notExistIn(std::vector<std::string> &AlreadyAddedNodes, std::string nodeAlias);
    int generate_OCM(void);

};
#endif /*GENOCM_H*/
