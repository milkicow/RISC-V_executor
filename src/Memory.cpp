#include "Memory.hpp"

bool Memory::write (uint32_t addr, uint32_t value, size_t size)
{
    if (addr + size > MEM_SIZE)
    {
        std::cout << "FAIL addr + size > MEM_SIZE: " << unsigned(addr) << " + " << unsigned(size) << " > " << unsigned(MEM_SIZE) << std::endl;
        return false;
    }
    // std::cout << "addr = " << addr << std::endl;
    std::memcpy(mem_ + addr, &value, 4);
    return true;
};

bool Memory::read (uint32_t addr, uint32_t * value, size_t size)
{
    if (addr + size > MEM_SIZE)
    {
        std::cout << "FAIL addr + size > MEM_SIZE: " << unsigned(addr) << " + " << unsigned(size) << " > " << unsigned(MEM_SIZE) << std::endl;
        return false;
    }

    std::memcpy(value, mem_ + addr, size);
    //std::cout << "value in read func = " << std::hex << *value << std::endl;
    return true;
};

void Memory::DumpMem()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {   
        if (mem_[i] != 0)
            printf("%02x", mem_[i]);
    }
    std::cout << std::endl;
};
