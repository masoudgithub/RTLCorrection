#include <iostream>
#include "genOCM.h"

int main()
{

    string dotFileName = "fir_main.dot";
    int  numberOfNodes = returnNumberOfNodes(dotFileName.c_str());
    std::cout << numberOfNodes << std::endl;
    OCMNode *rowNodes = new OCMNode[numberOfNodes];
    fillRowNodes(dotFileName.c_str(), rowNodes, numberOfNodes);
    return 0;
}
