#include <iostream>
#include "assembler.h"

/*
Here is the bash command I use to compile and run the assembler:
g++ -std=c++20 assembler_test.cpp assembler.cpp -o assembler_test && ./assembler_test

Here is the bash command I use to run the dissassembler, if it's installed:
xxd -o 0x80001000 -c 4 -g 4 ../CS3339_FINAL_PROJEC/program.bin | awk '{print $1,$2}' | ./bin/mipsdis -
*/

int main() {
    assembler my_assembler(true);
    my_assembler.process_assembly_file("assembly_file.asm");
    return 0;
}