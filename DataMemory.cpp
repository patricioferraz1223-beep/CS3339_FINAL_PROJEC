#include "DataMemory.h"
#include <iostream>

using namespace std;

int DataMemory::read(int address, bool memRead) {
    if (memRead) {
        if (memory.count(address)) 
        {
            return memory[address];
        }
        return 0;
    }
    return 0;
}

void DataMemory::write(int address, int value, bool memWrite) 
{
    if (memWrite) {
        memory[address] = value;
    }
};

// Print memory contents 
void  DataMemory::printMemory() {
    cout << "=== Data Memory ===" << endl;
    if (memory.empty()) {
        cout << "Memory is empty" << endl;
        return;
    }
    for (auto& pair : memory) {
        cout << "Address: " << pair.first
            << " | Value: " << pair.second << endl;
    }
    cout << endl;
}
