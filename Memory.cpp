#include "Memory.hpp"

bool Memory::write (uint32_t addr, uint32_t value, size_t size)
{
    if (addr + size > MEM_SIZE)
    {
        std::cout << "FAIL addr + size > MEM_SIZE: " << unsigned(addr) << " + " << unsigned(size) << " > " << unsigned(MEM_SIZE) << std::endl;
        return false;
    }

    std::memcpy(mem_ + addr, &value, size);
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
    return true;
};

void Memory::DumpMem()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        std::cout << mem_[i];
    }
};
