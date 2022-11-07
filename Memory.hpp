#ifndef MEMORY_H
#define MEMORY_H

#include "libs.hpp"

class Memory final
{
private:
    char mem_[MEM_SIZE] = {};

public:

    bool write (uint32_t addr, uint32_t value, size_t size);
    bool read (uint32_t addr,  uint32_t * value, size_t size);
};

#endif 
