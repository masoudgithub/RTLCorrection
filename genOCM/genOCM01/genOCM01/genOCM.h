#include <iostream>

using namespace std;

struct OCMNode
{
    string alias;
    string name;
    string type;
    int numberOfInputs;
    string *inputName;
    string *inputAlias;
};

int returnNumberOfNodes (const char *fileName);
void fillRowNodes(const char *fileName, OCMNode *rowNodes,int numberOfNodes);
