#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <unordered_map>
#include <iostream>
using namespace std;

class DataMemory {
private:
    // stores address and value pairs
    unordered_map<int, int> memory;

public:
    // Read from memory (for LW)
    // Only reads if memRead signal is on
    int read(int address, bool memRead) {
        if (memRead) {
            if (memory.count(address)) 
            {
                return memory[address];
            }
            return 0;
        }
        return 0;
    }

    // Write to memory (for SW)
    // Only actually writes if memWrite signal is on
    void write(int address, int value, bool memWrite) 
    {
        if (memWrite) {
            memory[address] = value;
        }
    }
};

#endif