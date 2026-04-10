#include <iostream>
/*/////////////////////////////////////////////////////////////////////////////////////////
While there are remaining instructions:
- Program counter outputs the address of the current instruction
- Instruction memory outputs the instruction at the address given by the program counter

Instruction Fetch (IF):

    Program Counter:
    - INPUT: 32-bit address
    - OUTPUT: 32-bit instruction address 
    Instruction Memory:
    - INPUT: 32-bit instruction address (from PC)
    - OUTPUT: 32-bit instruction
    Adder:
    - INPUT: Program counter + 4
    - OUTPUT: 32-bit address of next instruction

Instruction Decode (ID) Stage:

    Control Unit:
    - INPUT: bits 31-26 of instruction
    - OUTPUT: 10 control signals; uint16_t
    - NOTE: Each control signal is 1 bit, except for the ALUOp signal which is 2 bits (bits 1-0 of control output)
    Mux 1:
    - INPUT: bits 15-0 of instruction
    - INPUT: bits 20-16 of instruction
    - INPUT: Control Unit output
    - OUTPUT: 16-bit value ()
    Register File:
    - INPUT: bits 25-21 of instruction (Read Addr 1)
    - INPUT: bits 20-16 of instruction (Read Addr 2)
    - INPUT: Write address (Mux 1 output)
    - INPUT: Write Data (32 bits, from WB stage)
    - INPUT: Control Unit output
    - OUTPUT: Read Data 1 (32 bits)
    - OUTPUT: Read Data 2 (32 bits)
    Sign Extend:
    - INPUT: bits 15-0 of instruction
    - OUTPUT: 32-bit sign-extended value

Execute (EX) Stage:

    Shift Left 2:
    - INPUT : Sign Extend output (32 bit sign extended value)
    - OUTPUT: 32-bit value shifted left by 2 bits
    Adder:
    - INPUT: Program counter + 4
    - INPUT: SL2 output
    - OUTPUT: 32-bit address of next instruction (for branch)
    Mux 2:
    - INPUT: Read Data 2 from Register File
    - INPUT: Sign Extend output
    - INPUT: Control Unit output
    - OUTPUT: 32-bit value (second operand for ALU)
    ALU
    - INPUT: 32-bit Register File output 1
    - INPUT: 32-bit Mux 2 output
    - INPUT: 2-bit Control Unit output
    - INPUT: 4-bit ALU Control output
    - OUTPUT: 32-bit ALU result
    - OUTPUT: Zero flag (1 bit)
    ALU Control
    - INPUT: 2-bit Control Unit output
    - OUTPUT: 4-bit operation code for ALU (uint4_t)

Memory (MEM) Stage:

    AND Gate:
    Mux 3:
    Data Memory:

Write back (WB) Stage:

    Mux 4:

ALU Control Encoding Example:

| ALU Control (4 bits) | Operation |
| -------------------- | --------- |
| 0000                 | AND       |
| 0001                 | OR        |
| 0010                 | ADD       |
| 0110                 | SUB       |
| 0111                 | SLT       |
| 1100                 | NOR       |


QUESTIONS:
1. How many output bits are there from the control unit?
2. Does each stage need to be parallelized for the sake of simulating pipelining? 
3. If the PC isn't what actually holds the instructions nor increments the instruction 
    address, what does it do?
3.1 On the same note, what is the input to the adder in the IF stage?
4. What is the 0 flag in the ALU?
5. Do we not care about the overflow flag in the ALU for this project?
//////////////////////////////////////////////////////////////////////////////////////////*/
int main() {
    return 0;
}