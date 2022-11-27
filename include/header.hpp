#ifndef HEADER_H
#define HEADER_H

#include "libs.hpp"

inline void ClearFile(std::string filename)
{
    std::fstream file(filename, std::ios_base::out);
    file.close();
}

inline uint32_t get_bits(uint32_t code, size_t head, size_t tail)
{
    const size_t MAX_BITS_INSTR = 32;
    assert(head >= tail);
    assert(MAX_BITS_INSTR > head);

    return ((code << (MAX_BITS_INSTR - head - 1)) >> (MAX_BITS_INSTR - head + tail - 1));
}

inline void dump_bits(uint32_t code, size_t head, size_t tail)
{
    const size_t MAX_BITS_INSTR = 32;
    assert(head >= tail);
    assert(MAX_BITS_INSTR > head);

    uint32_t bits = get_bits(code, head, tail);
    for (int i = head - tail; i >= 0; --i)
    {
        std::cout << (int)((bits >> i) & 1);
    }
    //std::cout << std::endl;
}

#endif