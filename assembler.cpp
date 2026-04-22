/*
Necessary instructions:
Opcode  Description
ADD     signed integer addition
ADDI    add immediate
SUB     signed integer subtraction
MUL     integer multiplication
AND     bitwise and operation
OR      bitwise or operation
SLL     shift left logical
SRL     shift right logical
LW      load word
SW      store word
BEQ     branch if equal to
J       jump
NOP     no op


Architecture design:
- I need something to assemble individual instructions into their binary format.
- I need something to load a file into instruction memory. The instruction memory is responsible for this.
- I need something to read each line from the filez
- I need something to loop through the assembly file

*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdlib>   
#include <sstream>

#include "assembler.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
assembler::assembler(bool debug) {
    assembler::debug = debug;
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
void assembler::process_assembly_file(std::string filename) {
    /////////////////////////////////////////////////////////////////////////////////////////////
    // OPEN INPUT AND OUTPUT FILES

    // create input and output filenames
    string input_filename = filename;
    string output_filename = "program.bin";

    // create input and output files streams
    std::ofstream output;
    std::ifstream input;

    // open input stream for reading
    input.open(input_filename);
    if (!input.is_open()) {
        cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
        exit(0);
    }

    /* open output file stream for writing */
    output.open(output_filename);
    if (!output.is_open()) {
        cerr << "Could not open output file " << output_filename << ". Exiting ..." << endl;
        exit(0);
    }

    if (assembler::debug) {
        cout << "Input file successfully opened: " << input_filename << endl;
        cout << "Output file successfully opened: " << output_filename << endl;
    }

    std::string instruction_line = "";

    /////////////////////////////////////////////////////////////////////////////////////////////
    // READ ASSEMBLY FILE LINE BY LINE, ASSEMBLE INSTRUCTIONS, AND WRITE TO OUTPUT FILE
    // FIXME: I need a first pass for my labels and a second pass for my instructions

    // First pass: increment instruction count, loading labels into the address table
    while (std::getline(input, instruction_line)) {
        if (assembler::debug) cout << "First pass: reading instruction " << assembler::instruction_count << endl;

        // Track Instruction index for Branch and Jump Instructions
        
        std::string label;
        label = instruction_line; 
        int line_length = instruction_line.length();

        // Check line if label, else instruction
        if (line_length > 0 && instruction_line[line_length - 1] == ':') { // Check if the line ends with a colon, indicating it's a label
            // FIXME: I think i need to store all but the last char of the label, otherwise the label will include the colon and not match the label used in the instruction
            label_addresses[label] = instruction_count * 4; // Store the instruction index for the label
        }
        else instruction_count++; // Increment instruction count for each instruction (not labels)
        
    }

    input.clear();        // clear EOF flag
    input.seekg(0);       // go back to beginning

    int i = 0;
    while (std::getline(input, instruction_line)) {
        if (assembler::debug) cout << "Second pass: reading instruction " << i << endl;

        // Track Instruction index for Branch and Jump Instructions
        
        std::string label;
        label = instruction_line; 
        int line_length = instruction_line.length();

        // TODO: Really, the last char should be ':' and this determines if it's a label or not
        // TODO: I also need to either deal with a label or process an instruction
        if (line_length > 0 && instruction_line[line_length - 1] == ':') { // Example labels
            // label_addresses[label] = instruction_count * 4; // Store the instruction index for the label
            
            // Do nothing
        }
        else {
            // Assemble the instruction into binary
            uint32_t instruction_binary = assembler::assemble_instruction(instruction_line);

            if (assembler::debug) cout << "Are we even trying to write to output?" << endl;

            // Convert from little endian to big endian and write to output file
            unsigned char bytes[4];
            bytes[0] = (instruction_binary >> 24) & 0xFF;
            bytes[1] = (instruction_binary >> 16) & 0xFF;
            bytes[2] = (instruction_binary >> 8)  & 0xFF;
            bytes[3] = (instruction_binary)       & 0xFF;

            if (assembler::debug) cout << endl << "Instruction: " << instruction_line << " -> 0x" << hex << instruction_binary << dec << endl;
            
            output.write(reinterpret_cast<char*>(bytes), 4);
        }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // CLOSE FILE STREAMS

    i++;

    }

    output.close();
    input.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// handle the temporary registers, the stack pointer, the return address, and the constant 
//  0 register. 

// - Assume Named MIPS register format, ignore '$'
// - then if the rest of the string is sp, we can map it to 29. 
// - If it sees ra, we can map it to 31. 
// - if it sees zero, we can map it to 0. 
// - Then, the temporary registers are the default condition in our case statement, and we 
//      can call string to int.
/////////////////////////////////////////////////////////////////////////////////////////////
int assembler::parse_register(std::string szRegister) {
    std::string reg = szRegister.substr(1);

    if (reg == "sp") return 29;
    else if (reg == "ra") return 31;
    else if (reg == "zero") return 0;
    else if (reg == "t8") return 24;
    else if (reg == "t9") return 25;
    else return (std::stoi(reg.substr(1)) + 8); // Convert the register number to an integer, ignoring the '$' character
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// FIXME: I still need to deal with special registers
uint32_t assembler::assemble_instruction (std::string instruction_line) {

    std::string op, r1, r2, r3;
    std::istringstream iss(instruction_line);
    iss >> op >> r1 >> r2 >> r3;
    uint32_t instruction_binary = 0;
    uint32_t opcode, funct, shamt;
    uint32_t rs, rt, rd;
    opcode = funct = shamt = rs = rt = rd = 0;

    // FIXME: I have a few encoders to finish (ex: intermediates)
    // FIXME: I still need to deal with special registers
    if (op == "ADD") { // ADD rd, rs, rt
        if (assembler::debug) cout << "Assembling ADD instruction: " << instruction_line << endl;

        // rd = rs + rt
        funct = 0x20;                 // function
        opcode = 0x00;
        shamt  = 0;

        rs = assembler::parse_register(r2);
        rt = assembler::parse_register(r3);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // TODO: Implement this
    else if (op == "ADDI") { // ADDI rt, rs, imm
        if (assembler::debug) cout << "Assembling ADDI instruction: " << instruction_line << endl;

        // rt = rs + imm
        instruction_binary |= 0x08;   // opcode
    }
    else if (op == "SUB") { // SUB rd, rs, rt
        if (assembler::debug) cout << "Assembling SUB instruction: " << instruction_line << endl;

        // rd = rs - rt
        funct = 0x22;                 // function
        opcode = 0x00;
        shamt  = 0;

        rs = assembler::parse_register(r2);
        rt = assembler::parse_register(r3);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "MUL") { // MUL rd, rs, rt
        if (assembler::debug) cout << "Assembling MUL instruction: " << instruction_line << endl;

        // rd = rs * rt
        // WARNING: depends on which MIPS variant your class is using
        // If your class treats MUL like a normal 3-register ALU op, this may differ.
        funct = 0x02;                 // function for MUL
        opcode = 0x1C;
        shamt  = 0;

        rs = assembler::parse_register(r2);
        rt = assembler::parse_register(r3);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "AND") { // AND rd, rs, rt
        if (assembler::debug) cout << "Assembling AND instruction: " << instruction_line << endl;

        // rd = rs & rt
        funct = 0x24;                 // function
        opcode = 0x00;
        shamt  = 0;

        rs = assembler::parse_register(r2);
        rt = assembler::parse_register(r3);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "OR") { // OR rd, rs, rt
        if (assembler::debug) cout << "Assembling OR instruction: " << instruction_line << endl;

        // rd = rs | rt
        funct = 0x25;                 // function
        opcode = 0x00;
        shamt  = 0;

        rs = assembler::parse_register(r2);
        rt = assembler::parse_register(r3);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // FIXME: I need to set shift amount
    else if (op == "SLL") { // SLL rd, rt, shamt
        if (assembler::debug) cout << "Assembling SLL instruction: " << instruction_line << endl;

        // rd = rt << shamt
        funct = 0x00;                 // function
        opcode = 0x00;
        rs = 0;

        shamt = (assembler::parse_register(r3));
        rt = assembler::parse_register(r2);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // FIXME: I need to set shift amount
    else if (op == "SRL") { // SRL rd, rt, shamt
        if (assembler::debug) cout << "Assembling SRL instruction: " << instruction_line << endl;

        // rd = rt >> shamt
        funct = 0x02;                 // function
        opcode = 0x00;
        rs = 0;

        shamt = (assembler::parse_register(r3));
        rt = assembler::parse_register(r2);
        rd = assembler::parse_register(r1);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // TODO: Implement this 
    else if (op == "LW") { // LW rt, offset(base)
        if (assembler::debug) cout << "Assembling LW instruction: " << instruction_line << endl;

        // rt = Memory[base + offset]
        instruction_binary |= 0x23;   // opcode
    }
    // TODO: Implement this
    else if (op == "SW") { // SW rt, offset(base)
        if (assembler::debug) cout << "Assembling SW instruction: " << instruction_line << endl;

        // Memory[base + offset] = rt
        instruction_binary |= 0x2B;   // opcode
    }
    else if (op == "BEQ") { // BEQ rs, rt, offset/label/immediate
        if (assembler::debug) cout << "Assembling BEQ instruction: " << instruction_line << endl;

        // if (rs == rt) then PC = PC + offset
        opcode = 0x04;   // opcode
        std::string label = r3; // Assuming the label is the third operand
        uint32_t label_address = 0;
        if (assembler::label_addresses.contains(label)) 
            label_address = assembler::label_addresses[label]; // Get the instruction index for the label
        else {/* TODO: Handle undefined label error
            print an error like:
            "Undefined label: LOOPX"
            stop assembling that instruction
            or stop the whole assembly process

            do not keep encoding
            do not invent an address
            do not default to zero
            */
        }
        int32_t current_address = instruction_count * 4; // Current instruction address in bytes
        int32_t offset = (label_address - (current_address + 4)) / 4;
        offset &= 0xFFFF; // Ensure offset is 16 bits

        rs = assembler::parse_register(r1);
        rt = assembler::parse_register(r2);

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (offset);

    }
    else if (op == "J") { // J target
        if (assembler::debug) cout << "Assembling J instruction: " << instruction_line << endl;
        // PC = target
        opcode = 0x02;   // opcode
        std::string label = r1;
        uint32_t label_address = 0;
        if (assembler::label_addresses.contains(label)) 
            label_address = assembler::label_addresses[label]; // Get the instruction index for the label
        else {/* TODO: Handle undefined label error
            print an error like:
            "Undefined label: LOOPX"
            stop assembling that instruction
            or stop the whole assembly process

            do not keep encoding
            do not invent an address
            do not default to zero
            */
        }
        label_address /= 4; // convert byte address into the 26-bit jump target field value
        label_address &= 0x3FFFFFF; // Ensure label address is 26 bits

        instruction_binary |= (opcode << 26);
        instruction_binary |= label_address; // Assuming label_address is the target address
    }
    else if (op == "NOP") { // NOP
        if (assembler::debug) cout << "Assembling NOP instruction: " << instruction_line << endl;

        // NOP = SLL $0, $0, 0
        instruction_binary = 0;    
    }    
    else {
        instruction_binary = 0;    
    }
    
    return instruction_binary;
}
/////////////////////////////////////////////////////////////////////////////////////////////