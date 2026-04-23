#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <unordered_map>

class DataMemory {
private:
    std::unordered_map<int, int> memory;
public:
    int read(int address, bool memRead);
    void write(int address, int value, bool memWrite);
};

#endif