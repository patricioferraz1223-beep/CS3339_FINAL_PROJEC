/*
This file contains the assembler. Currently, I'm whiteboarding my design.





// Create a text string, which is used to output the text file
string instruction;

// Read from the text file
ifstream MyReadFile("filename.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, instruction)) {
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

*/