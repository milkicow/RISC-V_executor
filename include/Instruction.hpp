#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "libs.hpp"


class Instruction final

{
private:
    uint8_t type;
    RegId rd_, rs1_, rs2_;
    uint32_t imm_;
    InstId inst_tp_;

public:

    Instruction(uint32_t code);
    InstId get_inst_tp_() const { return inst_tp_; }
    RegId get_rd_() const { return rd_; }
    RegId get_rs1_() const { return rs1_; }
    RegId get_rs2_() const { return rs2_; }
    uint32_t get_imm_() const { return imm_; }

    void Dump()
    {   
        std::fstream log_file("logfile.txt", std::ios_base::app);
        log_file << "instruction " << InstIdName[inst_tp_] << " : "<< std::endl;
        log_file << " rd_ = " << rd_ << " rs1_ = " << rs1_ << " rs2_ = " << rs2_ << std::endl;
        log_file << " imm_ = " << std::dec << imm_ << std::endl;
        log_file.close();
    }
};

#endif