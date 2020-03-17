# RTLCorrection
This document helps you to use this tool to correct an Buggy RTL design

## Description
The input to the tool is the Verilog file of the buggy RTL design, the input C description
of the design. The output will be the corrected RTL design that is similar to the buggy one. 

## explaning the folders
We call the path that this README.md file contain the root.
The other folders and pathes explained here under the root. 

1. **genOCM**: This folder contains the main developement files. 
- **mainNode.h** and **mainNode.cpp** which implement the data structure for for both operations of the CDFG and resources of the RTL
- **genOCM.h** and **genOCM.cpp** that implement tha class that provide all the functions needed for creating Processig subgraphs. 
- **BipartiteWeightedMatchingBinding.h** and **BipartiteWeightedMatchingBinding.cpp** that are codes from LegUp itself, which are modified to fulfill our purposes

2. **editDotfil**: This folder contains a simple code and binary with the aim of modifying the .dot file the netlist outout of the Yosys tool.
    
3. **Matching**: contains the matching algorithm and its binary based on hungrian matching method. This binary are used to find the final result. 

4. **Other**: Contains small scripts to run the whole tool

5. **runTest**: contains the python script that forcasts the CPU time of a mutation based method. 


1- Reading output files of verilog parser (yosys) (the dot files)

2- reading the IR file (.LL) output of LLVM parser

3- considering resource and connections of original rtl (output of phase 1) 

The development is in progress ...
