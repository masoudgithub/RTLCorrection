#include <iostream>
#include <map>
#include <string>

class OCMNode
{
public:
    std::string alias;
    std::string name;
    std::string type;
    std::string portA;
    std::string portB;
    std::string portD;
    std::string portS;
    std::string portCLK;
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

typedef std::map<std::string,OCMNode> nodeMap;

void fillOCMRowNodes(const char *fileName, std::map <std::string, OCMNode> &ocmNodeMap);
void findConnections(const char *fileName, std::map <std::string, OCMNode> &ocmNodeMap);
int returnNumberOfreducedNodes(std::map <std::string, OCMNode> &ocmNodeMap, std::map <std::string, OCMNode> &reducedNodeMap);
void findExpandedInputsOfReducedNodeMap(std::map <std::string, OCMNode> &ocmNodeMap, std::map <std::string, OCMNode> &reducedNodeMap);
void findExpandedInputsforNode(std::string aliasOCM, std::map <std::string, OCMNode> &ocmNodeMap, std::string aliasRED, std::map <std::string, OCMNode> &reducedNodeMap);
void fillExpandedInputsforNode(std::string aliasOCM, std::map <std::string, OCMNode> &ocmNodeMap, std::string aliasRED, std::map <std::string, OCMNode> &reducedNodeMap);
bool isItMainType(std::string type);
bool isItStopType(std::string type);
bool isItGateType(std::string type);
bool isItShadowType(std::string type);
void findPort(std::string line, OCMNode &tempNode);
bool isItDataConnection(std::string line, std::string childNodeAlias, nodeMap &ocmNodeMap);
