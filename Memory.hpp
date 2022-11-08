#ifndef MEMORY_H
#define MEMORY_H

#include "libs.hpp"

class Memory final
{
private:
    char mem_[MEM_SIZE] = {};

public:
    char * GetMemAddr () { return mem_; }
    void DumpMem();
    bool write (uint32_t addr, uint32_t value, size_t size);
    bool read (uint32_t addr,  uint32_t * value, size_t size);
};

#endif 
