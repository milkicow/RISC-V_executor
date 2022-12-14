#ifndef CORE_H
#define CORE_H

#include "libs.hpp"
#include "Memory.hpp"

class Core final
{
private:

    Memory * mem_;
    uint32_t regs_[REGS_NUMBER] = {};

    uint32_t pc_ = 0;
    uint32_t next_pc_ = 0;


public:

    Core(Memory * mem) : mem_(mem) {}
    void SetReg (RegId id, uint32_t value) { regs_[id] = value; }
    void SetPc (uint32_t pc) { pc_ = pc; }
    void SetNextPc (uint32_t next_pc) { next_pc_ = next_pc; }
    uint32_t GetReg (RegId id) const { return regs_[id]; }
    uint32_t GetPc () const { return pc_; }
    uint32_t GetNextPc () const { return next_pc_; };
    void branch (uint32_t target) { 
        next_pc_ = target; 
    }
    void IncPc () {
        pc_ += INSTRUCTION_SIZE;
    }
    void Dump () const;
    bool execute (Memory * mem);

    bool write (uint32_t addr, uint32_t value, size_t size) { return mem_->write(addr, value, size); }
    bool read (uint32_t addr, uint32_t * value, size_t size) { return mem_->read(addr, value, size); }
};


#endif