#include <iostream>
#include "assembler.h"

int main() {
    assembler my_assembler(true);
    my_assembler.process_assembly_file("assembly_file.asm");
    return 0;
}