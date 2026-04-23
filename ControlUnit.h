#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <cstdint>

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

ControlSignals controlUnit(uint8_t opcode);

#endif