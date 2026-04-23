#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdlib>   


class assembler {
    
    public:
        void process_assembly_file(std::string filename);
        assembler(bool debug);
    private:
        // For tracking label addresses for branch and jump instructions
        std::unordered_map<std::string, uint32_t> label_addresses; 
        int instruction_count = 0;

        int parse_register(std::string szRegister);

        // FIXME: I still need to deal with special registers
        uint32_t assemble_instruction (std::string line, int instruction_index);

        bool debug = false;
};