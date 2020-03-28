# RTLCorrection
This document helps you to use this tool to correct an Buggy RTL design

## Description
The input to the tool is the Verilog file of the buggy RTL design, the input C description
of the design. The output will be the corrected RTL design that is similar to the buggy one. 

## Prequisities
1. You need to have LegUp (the open source high level synthesis tool) installed. 
   It is recommended to download the whole virtual box OS image of the LegUp from 
   http://legup.eecg.utoronto.ca/. 
   After opening the OS containing the LegUp or intalling the LegUp on Linux, you can see the 
   **legup-4.0** in your home folder.
2. You need to have Yosys (the open source verilog compiler) installed. After successful intallation,
   you can see the **yosys-master** folder in your home folder. 

## Explaining the repo structure
We call the path of this README.md file the root.
The other folders and pathes explained here are under the root. 

1. **genOCM folder**: It contains the main developement files. 
- *mainNode.h* and *mainNode.cpp* which implement the data structure for for both operations of 
  the CDFG (OPS) and resources of the RTL (RPS).
- *genOCM.h* and *genOCM.cpp* that implement the class that provide all the functions needed for
  creating Processig Subgraphs (PS). 
- *BipartiteWeightedMatchingBinding.h* and *BipartiteWeightedMatchingBinding.cpp* that are codes
  from LegUp itself, which are modified to fulfill our purposes. 

2. **editDotfil folder**: It contains a simple code and binary with the aim of modifying the .dot 
   file (the netlist outout of the Yosys tool).
    
3. **Matching folder**: It contains the matching algorithm and its binary based on hungrian matching
   method. This binary is used to find the final result. 

4. **other folder**: It Contains small scripts to run the whole tool

5. **runTest folder**: It contains the python script that forcasts the CPU time of a mutation based method. 

## How to make the toolchain ready 
Here we explain how to patch the LegUp and Yosys.
Before making the patches, make copy of the *legup-4.0* in the same path it is and rename it
to *original_legup*. The *original_legup* will be used to create the buggy verilog files. 
1. **Patch the Yosys:**
-  Replace the *yosys-master/passes/cmds/show.cc* with the *other/show.cc*
2. **Patch the legUp:**
-  Replace the **legup-4.0/examples/Makefile.common** with **other/makefile.common**
-  Copy the whole content of **other/genOCM** folder to the **legup-4.0/llvm/lib/Target/Verilog**
   Answer yes to the question about replacing files.

## How to correct an RTL design
Here we explain the way you can correct a buggy RTL design. 
To have buggy RTL design, we use LegUp to sythesize a buggy C code to a verilog code.

1- Modify the buggy RTL code to remove 

1- Reading output files of verilog parser (yosys) (the dot files)

2- reading the IR file (.LL) output of LLVM parser

3- considering resource and connections of original rtl (output of phase 1) 

The development is in progress ...
