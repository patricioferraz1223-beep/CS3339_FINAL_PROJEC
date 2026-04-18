/*
This file contains the assembler. Currently, I'm whiteboarding my design.


// Create a text string, which is used to output the text file
string instruction;

// Read from the text file
ifstream MyReadFile("filename.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, instruction)) {
    std::string line = "add $t0 $t1 $t2";

    std::istringstream iss(line);

    std::string op, r1, r2, r3;
    iss >> op >> r1 >> r2 >> r3;

    std::cout << op << "\n";  // add
    std::cout << r1 << "\n";  // $t0
    std::cout << r2 << "\n";  // $t1
    std::cout << r3 << "\n";  // $t2

}

// Close the file
MyReadFile.close();


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
- I need something to load a file into instruction memory.
- I need something to read each line from the file
- I need something to loop through the assembly file

What I'm currently working on is how to divide the responsibilities between the instruction memory and the assembler. 

I think the assembler can be its own function, while the instruction memory has separete load individual instructions and a load file function.

*/
#include <iostream>
#include <fstream>

int reg_to_int(std::string reg) {
    // assumes format "R<number>"
    return std::stoi(reg.substr(1));
}

// FIXME: I still need to deal with special registers
uint32_t assemble_instruction () {

    std::istringstream instruction_line(line);

    std::string op, r1, r2, r3;
    instruction_line >> op >> r1 >> r2 >> r3;
    uint32_t instruction_binary = 0;
    uint32_t opcode, funct, shamt;
    uint32_t rs, rt, rd;

    if (op == "ADD") { // ADD rd, rs, rt
        // rd = rs + rt
        funct = 0x20;                 // function
        opcode = 0x00;
        shamt  = 0;


        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "ADDI") { // ADDI rt, rs, imm
        // rt = rs + imm
        instruction_binary |= 0x08;   // opcode
    }
    else if (op == "SUB") { // SUB rd, rs, rt
        // rd = rs - rt
        funct = 0x22;                 // function
        opcode = 0x00;
        shamt  = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "MUL") { // MUL rd, rs, rt
        // rd = rs * rt
        // WARNING: depends on which MIPS variant your class is using
        // If your class treats MUL like a normal 3-register ALU op, this may differ.
        funct = 0x02;                 // function for MUL
        opcode = 0x1C;
        shamt  = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "AND") { // AND rd, rs, rt
        // rd = rs & rt
        funct = 0x24;                 // function
        opcode = 0x00;
        shamt  = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "OR") { // OR rd, rs, rt
        // rd = rs | rt
        funct = 0x25;                 // function
        opcode = 0x00;
        shamt  = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // FIXME: I need to set shift amount
    else if (op == "SLL") { // SLL rd, rt, shamt
        // rd = rt << shamt
        funct = 0x00;                 // function
        opcode = 0x00;
        rs = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    // FIXME: I need to set shift amount
    else if (op == "SRL") { // SRL rd, rt, shamt
        // rd = rt >> shamt
        funct = 0x02;                 // function
        opcode = 0x00;
        rs = 0;

        instruction_binary |= (opcode << 26);
        instruction_binary |= (rs     << 21);
        instruction_binary |= (rt     << 16);
        instruction_binary |= (rd     << 11);
        instruction_binary |= (shamt  << 6);
        instruction_binary |= (funct);
    }
    else if (op == "LW") { // LW rt, offset(base)
        // rt = Memory[base + offset]
        instruction_binary |= 0x23;   // opcode
    }
    else if (op == "SW") { // SW rt, offset(base)
        // Memory[base + offset] = rt
        instruction_binary |= 0x2B;   // opcode
    }
    else if (op == "BEQ") { // BEQ rs, rt, offset/label/immediate
        // if (rs == rt) then PC = PC + offset
        instruction_binary |= 0x04;   // opcode
    }
    else if (op == "J") { // J target
        // PC = target
        instruction_binary |= 0x02;   // opcode
    }
    else if (op == "NOP") { // NOP
        // NOP = SLL $0, $0, 0
        instruction_binary = 0;    
    }    
    else {
        instruction_binary = 0;    
    }
    

    return 0;
}