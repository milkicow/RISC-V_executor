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
    uint32_t GetPc() { return pc_; }
    uint32_t GetNextPc() { return pc_ + 1; };
    void branch(uint32_t target) { next_pc_ = target; }
    void IncPc() {
        pc_ += InstructionSize;
        next_pc_ += InstructionSize;
    }

    void Dump() {
        std::fstream log_file("logfile.txt", std::ios_base::app);
        log_file << "*--------------------------------------------------* \n";
        log_file << " pc = " << GetPc() << " next_pc = " << GetNextPc() << std::endl;

        for (int i = 0; i < REGS_NUMBER ; i++) {
            log_file << "REG_" << std::setw( 2 ) << std::setfill( '0' ) << i << " = " << regs_[i] << std::endl;
        }

        log_file << "*--------------------------------------------------* \n\n";
        log_file.close();
    }
};

#endif
