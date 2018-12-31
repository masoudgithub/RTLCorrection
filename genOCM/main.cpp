#include <iostream>
#include "genOCM.h"
#include <string>

// inputs "xx.ll" "first xx.dot" "second xx.dot" ...
int main(int argc, char *argv[])
{
    genOCM mainGenOCM;
    mainGenOCM.generate_OCM();
    return 0;
}
