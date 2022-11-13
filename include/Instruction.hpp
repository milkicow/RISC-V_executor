#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "libs.hpp"
#include "Core.hpp"
#include "Memory.hpp"


class Instruction final

{
private:

    enum InstId
    {
        LUI, AUIPC, 
        SLLI, SRLI, SRAI,
        ADD, SLT, SLTU,
        AND, OR, XOR,
        SLL, SRL,
        SUB, SRA,
        ADDI, SLTI, SLTIU,
        ANDI, ORI, XORI,
        JAL, JALR,
        ERROR,
        LB, LH, LW, LBU, LHU,
        SB, SH, SW,
        BEQ, BNE, BLT, BGE, BLTU, BGEU

    };

    static constexpr char InstIdName[][10]
    {
        "LUI", "AUIPC", 
        "SLLI", "SRLI", "SRAI",
        "ADD", "SLT", "SLTU",
        "AND", "OR", "XOR",
        "SLL", "SRL",
        "SUB", "SRA",
        "ADDI", "SLTI", "SLTIU",
        "ANDI", "ORI", "XORI",
        "JAL", "JALR",
        "ERROR",
        "LB", "LH", "LW", "LBU", "LHU",
        "SB", "SH", "SW",
        "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU"
    };


    Core * core;

    uint8_t type;
    RegId rd_, rs1_, rs2_;
    uint32_t imm_;
    InstId inst_tp_;
    bool exec_status_;


    bool executeAUIPC(Core *core);
    bool executeLUI(Core *core);
    bool executeSLLI(Core *core);
    bool executeSRLI(Core *core);
    bool executeSRAI(Core *core);
    bool executeADD(Core *core);
    bool executeSLT(Core *core);
    bool executeSLTU(Core *core);
    bool executeAND(Core *core);
    bool executeOR(Core *core);
    bool executeXOR(Core *core);
    bool executeSLL(Core *core);
    bool executeSRL(Core *core);
    bool executeSUB(Core *core);
    bool executeSRA(Core *core);
    bool executeADDI(Core *core);
    bool executeSLTI(Core *core);
    bool executeSLTIU(Core * core);
    bool executeANDI(Core *core);
    bool executeORI(Core *core);
    bool executeXORI(Core *core);
    bool executeJAL(Core *core);
    bool executeJALR(Core *core);
    bool executeLB(Core *core);
    bool executeLH(Core *core);
    bool executeLW(Core *core);
    bool executeLBU(Core *core);
    bool executeLHU(Core *core);
    bool executeSB(Core *core);
    bool executeSH(Core *core);
    bool executeSW(Core *core);
    bool executeBEQ(Core *core);
    bool executeBNE(Core *core);
    bool executeBLT(Core *core);
    bool executeBGE(Core *core);
    bool executeBLTU(Core *core);
    bool executeBGEU(Core *core);

public:

    uint32_t get_bits(uint32_t code, size_t head, size_t tail);
    void dump_bits(uint32_t, size_t head, size_t tail);
    void Dump()
    {   
        std::fstream log_file("logfile.txt", std::ios_base::app);
        log_file << "instruction " << InstIdName[inst_tp_] << " : "<< std::endl;
        log_file << " rd_ = " << rd_ << " rs1_ = " << rs1_ << " rs2_ = " << rs2_ << std::endl;
        log_file << " imm_ = " << std::dec << imm_ << std::endl;
        log_file.close();
    }
    Instruction(Core *core, uint32_t code);
    bool GetExexStatus() { return exec_status_; }
};

#endif