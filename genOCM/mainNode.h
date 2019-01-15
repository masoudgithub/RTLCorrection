#ifndef MAINNODE_H
#define MAINNODE_H
class mainNode
{
public:
	mainNode();
	~mainNode();
    std::string inOutType = "NON";
    std::string moduleName;
    std::string alias;
    std::string name;
    std::string nameNumbered;
    std::string typeComplete;
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

    void clearInputIndexe(); 
    void clearEXPInputIndex();

};

#endif
