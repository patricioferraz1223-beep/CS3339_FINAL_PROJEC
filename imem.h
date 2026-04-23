#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

/*/////////////////////////////////////////////////////////////////////////////////////////
    Instruction Memory:
    - INPUT: 32-bit instruction address (from PC)
    - OUTPUT: 32-bit instruction
//////////////////////////////////////////////////////////////////////////////////////////*/
class InstructionMemory {
    private:
        std::vector<uint8_t> imem_data; // Vector to hold the instruction memory data
        std::vector<uint8_t> load_binary(const std::string& filename);

        int get_size();

    public:
        InstructionMemory();
        InstructionMemory(const std::string& filename);

        uint32_t read_address(uint32_t address);

        void load_instructions(const std::string& filename);
};

