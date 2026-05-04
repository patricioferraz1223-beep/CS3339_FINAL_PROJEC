#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <cstdint>
#include <iostream>

class RegisterFile 
{
private:
    uint32_t registers[32];
public:
    RegisterFile();
    void read(uint8_t rs, uint8_t rt, uint32_t &data1, uint32_t &data2);
    void write(uint8_t rd, uint32_t data, bool regWrite);
    void print_registers();
};

#endif