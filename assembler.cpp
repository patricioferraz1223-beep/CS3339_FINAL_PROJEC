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

uint32_t assemble_instruction () {

    std::istringstream instruction_line(line);

    std::string op, r1, r2, r3;
    instruction_line >> op >> r1 >> r2 >> r3;

    if (op == "ADD")
    else if (op == "ADDI")
    else if (op == "SUB")
    else if (op == "MUL")
    else if (op == "AND")
    else if (op == "OR")
    else if (op == "SLL")
    else if (op == "SRL")
    else if (op == "LW")
    else if (op == "SW")
    else if (op == "BEQ")
    else if (op == "J")
    else if (op == "NOP")
    else {
        std::cout << "Invalid instruction: " << op << "\n";
    }
    

    return 0;
}