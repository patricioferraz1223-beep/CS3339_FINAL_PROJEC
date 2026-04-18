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

uint32_t assemble_instruction () {

    std::istringstream instruction_line(line);

    std::string op, r1, r2, r3;
    instruction_line >> op >> r1 >> r2 >> r3;
    std::string instruction_binary = "";

    if (op == "ADD") { // ADD rd, rs, rt {}
        // rd = rs + rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "ADDI") { // ADDI rt, rs, imm
        // rt = rs + imm
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // immediate

    }
    else if (op == "SUB") { // SUB rd, rs, rt
        // rd = rs - rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "MUL") { // MUL rd, rs, rt
        // rd = rs * rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "AND") { // AND rd, rs, rt
        // rd = rs & rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "OR") { // OR rd, rs, rt
        // rd = rs | rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "SLL") { // SLL rd, rt, shamt
        // rd = rt << shamt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }

    else if (op == "SRL") { // SRL rd, rt, shamt
        // rd = rt >> shamt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // rd
    }
    else if (op == "LW") { // LW rt, offset(base)
        // rt = Memory[base + offset]
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // immediate
    }
    else if (op == "SW") { // SW rt, offset(base)
        // Memory[base + offset] = rt
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // immediate
    }
    else if (op == "BEQ") { // BEQ rs, rt, offset/label/immediate
        // if (rs == rt) then PC = PC + offset
        instruction_binary += ""; // opcode
        instruction_binary += ""; // rs
        instruction_binary += ""; // rt
        instruction_binary += ""; // immediate
    }
    else if (op == "J") { // J target
        // PC = target
        instruction_binary += ""; // opcode
        instruction_binary += ""; // target
    }
    else if (op == "NOP") { // NOP
        // do nothing
        instruction_binary += ""; // opcode
    }
    else {
        std::cout << "Invalid instruction: " << op << "\n";
    }
    

    return 0;
}