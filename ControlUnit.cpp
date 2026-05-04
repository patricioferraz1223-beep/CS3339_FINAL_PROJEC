#include <cstdint>
#include <iostream>
using namespace std;


// The signals the Control Unit outputs
struct ControlSignals {
    bool regDst;    // 0 = rt gets result, 1 = rd gets result
    bool aluSrc;    // 0 = use register, 1 = use immediate
    bool memToReg;  // 0 = from ALU, 1 = from memory
    bool regWrite;  // 1 = write to register
    bool memRead;   // 1 = read from memory (LW)
    bool memWrite;  // 1 = write to memory (SW)
    bool branch;    // 1 = this is BEQ
    bool jump;      // 1 = this is J
    uint8_t aluOp;  // 2 bits: 00=LW/SW, 01=BEQ, 10=R-type
};


/* The Control Unit function
   Takes the opcode (bits 31-26 of instruction)
   Returns a bundle of control signals
*/
ControlSignals controlUnit(uint8_t opcode) {
    
    // Start with everything off/false
    ControlSignals s = {};

    switch(opcode) {
        case 0x00:  // R-type (ADD, SUB, AND, OR, SLL, SRL)
            s.regDst   = true;
            s.regWrite = true;
            s.aluOp    = 0b10;
            break;

        case 0x1C:  // MUL special opcode
            s.regDst   = true;
            s.regWrite = true;
            s.aluOp    = 0b11;
            break;

        case 0x08:  // ADDI
            s.aluSrc   = true;
            s.regWrite = true;
            s.aluOp    = 0b00;
            break;

        case 0x23:  // LW
            s.aluSrc   = true;
            s.memToReg = true;
            s.regWrite = true;
            s.memRead  = true;
            s.aluOp    = 0b00;
            break;

        case 0x2B:  // SW
            s.aluSrc   = true;
            s.memWrite = true;
            s.aluOp    = 0b00;
            break;

        case 0x04:  // BEQ
            s.branch   = true;
            s.aluOp    = 0b01;
            break;

        case 0x02:  // J
            s.jump     = true;
            break;
    }
    return s;
}