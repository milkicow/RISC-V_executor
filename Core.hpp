#ifndef CORE_H
#define CORE_H

#include "libs.hpp"
#include "Memory.hpp"

class Core final
{
private:

    Memory * mem;
    uint32_t regs_[REGS_NUMBER] = {};

    uint32_t pc_ = 0;
    uint32_t next_pc_ = 1;


public: /*       !!!  WORK WITH STREAM OF COMMANDS UINT32_T BECAUSE OF THAT NEXT_PC_ == PC_ + 1  !!!   and do not work with jumps (as i understand)      */

    void SetReg (RegId id, uint32_t value) { regs_[id] = value; }
    uint32_t GetReg (RegId id) { return regs_[id]; }
    uint32_t GetPc () { return pc_; }
    uint32_t GetNextPc () { return next_pc_; };
    void branch (uint32_t target) { 
        next_pc_ = target; 
    }
    void IncPc () {
        pc_ += InstructionSize; // += 4 on char
    }
    void Dump ();

    bool write (uint32_t addr, uint32_t value, size_t size) { return mem->write(addr, value, size); }
    bool read (uint32_t addr, uint32_t * value, size_t size) { return mem->read(addr, value, size); }

};

#endif
