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


class RegisterFile 
{
private:
    uint32_t registers[32] = {0}; //Combining the number of registers and the value mapping variables
    //Creates the 32 registers (all 32 bits wide intialized to 0)

public:
    //Reading (on both register, which should happen twice per cycle)
    void read(uint8_t rs, uint8_t rt, uint32_t &data1, uint32_t &data2)
    {
        //Reading should happen combinationally, aka, instant without depending on a clock
        data1 = registers[rs];
        data2 = registers[rt];
    }

    //Writing (only one write per cycle, happens at the end of it, aka, sequentially)
    void write(uint8_t rd, uint32_t data, bool regWrite) 
    {
        if (regWrite && rd != 0) //Checks for the Control Signal AND the destination register
        {
            registers[rd] = data; //Now it actually writes the data to a register
        }
    }
};