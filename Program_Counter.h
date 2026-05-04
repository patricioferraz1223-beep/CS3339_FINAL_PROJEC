#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <cstdint>

class ProgramCounter 
{
private:
    uint32_t current_address; //Stores the PC's instruction address

public:
    //Constructor which sets the intial PC value (Let's the program begin at a known instruction address)
    ProgramCounter(uint32_t start_addr = 0);

    //Output (Goes to the instruction memory)
    uint32_t get_address();

    //Input (Updating for the next cycle)
    void update(uint32_t next_address);
};

#endif