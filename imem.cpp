#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "imem.h"

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    

    Instruction Memory:
    - INPUT: 32-bit instruction address (from PC)
    - OUTPUT: 32-bit instruction
//////////////////////////////////////////////////////////////////////////////////////////*/

std::vector<uint8_t> InstructionMemory::load_binary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    // Move to end to get file size
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate buffer
    std::vector<uint8_t> buffer(size);

    // Read entire file
    if (file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        return buffer;
    }

    throw std::runtime_error("Failed to read file");
}

InstructionMemory::InstructionMemory() {}

InstructionMemory::InstructionMemory(const std::string& filename) {
    load_instructions(filename);
}

uint32_t InstructionMemory::read_address(uint32_t address) {
    if (address + 3 >= imem_data.size()) {
        throw std::out_of_range("InstructionMemory: address out of bounds");
    }

    if (address % 4 != 0) {
        throw std::runtime_error("Unaligned instruction access");
    }

    uint32_t instr =
        (static_cast<uint32_t>(imem_data[address]) << 24) |
        (static_cast<uint32_t>(imem_data[address + 1]) << 16) |
        (static_cast<uint32_t>(imem_data[address + 2]) << 8)  |
        (static_cast<uint32_t>(imem_data[address + 3]));
    return instr;
}
void InstructionMemory::load_instructions(const std::string& filename) {
    // load binary file into array of bytes
    imem_data = load_binary(filename);
}

