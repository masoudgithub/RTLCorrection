#include <iostream>
#include <map>
#include <string>

class Node
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
};

typedef std::map<std::string,Node> nodeMap;
void fillOCMRowNodes(const char *fileName, nodeMap &ocmNodeMap, std::string moduleName);
void fillIRRowNodes(const char *fileName, std::map <std::string, Node> &IRNodeMap);
void findConnections(const char *fileName, std::map <std::string, Node> &ocmNodeMap);
void fillInOutType(std::map <std::string, Node> &ocmNodeMap);
int returnNumberOfreducedNodes(std::map <std::string, Node> &ocmNodeMap, std::map <std::string, Node> &reducedNodeMap);
void findExpandedInputsOfReducedNodeMap(std::map <std::string, Node> &ocmNodeMap, std::map <std::string, Node> &reducedNodeMap);
void findExpandedInputsforNode(std::string aliasOCM, std::map <std::string, Node> &ocmNodeMap, std::string aliasRED, std::map <std::string, Node> &reducedNodeMap);
void fillExpandedInputsforNode(std::string aliasOCM, std::map <std::string, Node> &ocmNodeMap, std::string aliasRED, std::map <std::string, Node> &reducedNodeMap);
bool isItMainType(std::string type);
bool isItStopType(std::string type);
bool isItGateType(std::string type);
bool isItShadowType(std::string type);
void findPort(std::string line, Node &tempNode);
bool isItDataConnection(std::string line, std::string childNodeAlias, nodeMap &ocmNodeMap);
bool isOperation(std::string line);
bool fillTempNodes(Node &tempNode1, Node &tempNode2, std::string line);
void fillGetelemData(Node &tempNode2, std::string line);
void fillGetphiData(Node &tempNode2, std::string line);
void fillGetloadData(Node &tempNode2, std::string line);
void fillotherOprData(Node &tempNode2, std::string line);
void fillEmptyAliases(std::map <std::string, Node> &IRNodeMap);
void findAndReplaceDuplicatedNodes(std::map <std::string, Node> &ocmNodeMap);
void showNodeMap (std::map <std::string, Node> &showNodeMap, const char* name);
void supportHierarchy(std::map <std::string, Node> &ocmNodeMap);
