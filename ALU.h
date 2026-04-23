#ifndef ALU_H
#define ALU_H

#include <cstdint>

uint32_t execute_alu(uint32_t A, uint32_t B, uint8_t shamt, uint8_t control_code, bool &zero_flag);

#endif