#include <iostream>
#include "mainNode.h"

mainNode::mainNode (void)
{
    inputIndex = 0;
    expandedInputIndex = 0;
    inputWidth = 32; // initial value
    /*std::cout<<"mainNode created."<<std::endl;*/
}

void mainNode::clearInputIndexe()
{

    inputIndex = 0;
}

void mainNode::clearEXPInputIndex()
{
    expandedInputIndex = 0;
}

mainNode::~mainNode (void)
{
    /*std::cout<<"mainNode deleted."<<std::endl;*/
}
