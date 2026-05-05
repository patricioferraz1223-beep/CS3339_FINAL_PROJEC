#include "DataMemory.h"
#include <iostream>
#include <iomanip>

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
        cout << "Address: 0x" << hex << std::setw(8) << setfill('0') << pair.first
            << " | Value: 0x" << hex << std::setw(8) << setfill('0') << pair.second << dec << endl;
    }
    cout << endl;
}
