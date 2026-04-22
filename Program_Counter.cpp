/*/////////////////////////////////////////////////////////////////////////////////////////
    Program Counter:
    - INPUT: 32-bit address
    - OUTPUT: 32-bit instruction address 
//////////////////////////////////////////////////////////////////////////////////////////*/

class ProgramCounter 
{
private:
    uint32_t current_address; //Stores the PC's instruction address

public:
    //Constructor which sets the intial PC value (Let's the program begin at a known instruction address)
    ProgramCounter(uint32_t start_addr = 0) : current_address(start_addr) {}

    //Output (Goes to the instruction memory)
    uint32_t get_address() 
    {
        return current_address;
    }

    //Input (Updating for the next cycle)
    void update(uint32_t next_address) 
    {
        current_address = next_address; //Updates the PC at the end of the cycle (Doesn't always need to be PC=PC+4)
    }
};