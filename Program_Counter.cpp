/*/////////////////////////////////////////////////////////////////////////////////////////
    Program Counter:
    - INPUT: 32-bit address
    - OUTPUT: 32-bit instruction address 
//////////////////////////////////////////////////////////////////////////////////////////*/
#include "Program_Counter.h"

ProgramCounter::ProgramCounter(uint32_t start_addr) : current_address(start_addr) {}

uint32_t ProgramCounter::get_address() 
{
    return current_address;
}

void ProgramCounter::update(uint32_t next_address) 
{
    current_address = next_address;
}