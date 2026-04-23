/*/////////////////////////////////////////////////////////////////////////////////////////
    Register File:
    - INPUT: bits 25-21 of instruction (Read Addr 1)
    - INPUT: bits 20-16 of instruction (Read Addr 2)
    - INPUT: Write address (Mux 1 output), 5 bits
    - INPUT: Write Data (32 bits, from WB stage)
    - INPUT: Control Unit output
    - OUTPUT: Read Data 1 (32 bits)
    - OUTPUT: Read Data 2 (32 bits)
//////////////////////////////////////////////////////////////////////////////////////////*/
#include "Register_File.h"
#include <iomanip>

RegisterFile::RegisterFile() {
    for (int i = 0; i < 32; i++) registers[i] = 0;
}

void RegisterFile::read(uint8_t rs, uint8_t rt, uint32_t &data1, uint32_t &data2)
{
    data1 = registers[rs];
    data2 = registers[rt];
}

void RegisterFile::write(uint8_t rd, uint32_t data, bool regWrite) 
{
    if (regWrite && rd != 0)
    {
        registers[rd] = data;
    }
}

void RegisterFile::print_registers() {
    for (int i = 0; i < 32; i++) {
        std::cout << "R" << std::setw(2) << i 
                << ": 0x" << std::hex << std::setw(8) << std::setfill('0') 
                << registers[i] << std::dec << std::setfill(' ')
                << std::endl;
    }
}