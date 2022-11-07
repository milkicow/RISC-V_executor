#include "Instruction.hpp"

Instruction::Instruction(Core *core, uint32_t code)
{
    inst_tp_ = ERROR;
    uint32_t type = code & 0x7F;

    switch (type)
    {
    case 0:
    {   
        exec_status_ = false;
        break;
    }
    case 0b0000011: // I-type 
    {
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = static_cast<int32_t> (get_bits(static_cast<int32_t> (code), 31, 20));
        
        auto funct3 = get_bits(code, 14, 12);

        if (funct3 == 0b000) // LB
        {
            inst_tp_ = LB;
            exec_status_ = Instruction::executeLB(core);
        }
        else if (funct3 == 0b001) // LH
        {
            inst_tp_ = LH;
            exec_status_ = Instruction::executeLH(core);
        }
        else if (funct3 == 0b010) // LW
        {
            inst_tp_ = LW;
            exec_status_ = Instruction::executeLW(core);
        }
        else if (funct3 == 0b100) // LBU
        {
            inst_tp_ = LBU;
            exec_status_ = Instruction::executeLBU(core);
        }
        else if (funct3 == 0b101) // LHU
        {
            inst_tp_ = LHU;
            exec_status_ = Instruction::executeLHU(core);
        }
        else 
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    }
    case 0b0010111: // U-type AUIPC
    {
        imm_ = get_bits(code, 31, 12);
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));

        //std::cout << "rd_ = " << rd_ << " imm_ = " << imm_ << std::endl;
        
        inst_tp_ = AUIPC;
        exec_status_ = Instruction::executeAUIPC(core);

        break;
    }
    case 0b0110111: // U-type LUI
    {
        imm_ = get_bits(code, 31, 12);
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));

        //std::cout << "rd_ = " << rd_ << " imm_ = " << imm_ << std::endl;

        inst_tp_ = LUI;
        exec_status_ = Instruction::executeLUI(core);

        break;
    }
    case 0b0010011: // I-type 
    {   
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = static_cast<int32_t> (get_bits(static_cast<int32_t> (code), 31, 20));
        
        auto funct3 = get_bits(code, 14, 12);
        auto funct7 = get_bits(imm_, 11, 5);

        if (funct3 == 0b000) // ADDI
        {
            inst_tp_ = ADDI;
            exec_status_ = Instruction::executeADDI(core);
        }
        else if (funct3 == 0b001) // SLTI
        {
            inst_tp_ = SLTI;
            exec_status_ = Instruction::executeSLTI(core);
        }
        else if (funct3 == 0b010) // SLTIU
        {
            inst_tp_ = SLTIU;
            exec_status_ = Instruction::executeSLTIU(core);
        }
        else if (funct3 == 0b111) // ANDI
        {
            inst_tp_ = ANDI;
            exec_status_ = Instruction::executeANDI(core);
        }
        else if (funct3 == 0b110) // ORI
        {
            inst_tp_ = ORI;
            exec_status_ = Instruction::executeORI(core);
        }
        else if (funct3 == 0b100) // XORI
        {
            inst_tp_ = XORI;
            exec_status_ = Instruction::executeXORI(core);
        }
        else if (funct7 == 0b0000000 && funct3 == 0b001) // SLLI
        {   
            inst_tp_ = SLLI;
            exec_status_ = Instruction::executeSLLI(core);
        }
        else if (funct7 == 0b0000000 && funct3 == 0b101) // SRLI
        {
            inst_tp_ = SRLI;
            exec_status_ = Instruction::executeSRLI(core);
        }
        else if (funct7 == 0b0100000 && funct3 == 0b101) // SRAI
        {
            inst_tp_ = SRAI;
            exec_status_ = Instruction::executeSRAI(core);
        }
        else
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    }
    case 0b0110011: // R-type
    {
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));

        //std::cout << "rd_ = " << rd_ << " rs1_ = " << rs1_ << " rs2_ = " << rs2_ << std::endl;

        auto funct3 = get_bits(code, 14, 12);
        auto funct7 = get_bits(code, 31, 25);

        if (funct3 == 0b000 && funct7 == 0b0000000) // ADD
        {
            inst_tp_ = ADD;
            exec_status_ = Instruction::executeADD(core);
        }
        else if (funct3 == 0b000 && funct7 == 0b0100000) // SUB
        {
            inst_tp_ = SUB;
            exec_status_ = Instruction::executeSUB(core);
        }
        else if (funct3 == 0b001 && funct7 == 0b0000000) // SLL
        {
            inst_tp_ = SLL;
            exec_status_ = Instruction::executeSLL(core);
        }
        else if (funct3 == 0b010 && funct7 == 0b0000000) // SLT
        {
            inst_tp_ = SLT;
            exec_status_ = Instruction::executeSLT(core);
        }
        else if (funct3 == 0b011 && funct7 == 0b0000000) // SLTU
        {
            inst_tp_ = SLTU;
            exec_status_ = Instruction::executeSLTU(core);
        }
        else if (funct3 == 0b100 && funct7 == 0b0000000) // XOR
        {
            inst_tp_ = XOR;
            exec_status_ = Instruction::executeXOR(core);
        }
        else if (funct3 == 0b101 && funct7 == 0b0000000) // SRL
        {
            inst_tp_ = SRL;
            exec_status_ = Instruction::executeSRL(core);
        }
        else if (funct3 == 0b101 && funct7 == 0b0100000) // SRA
        {
            inst_tp_ = SRA;
            exec_status_ = Instruction::executeSRA(core);
        }
        else if (funct3 == 0b110 && funct7 == 0b0000000) // OR
        {
            inst_tp_ = OR;
            exec_status_ = Instruction::executeOR(core);
        }
        else if (funct3 == 0b111 && funct7 == 0b0000000) // AND
        {
            inst_tp_ = AND;
            exec_status_ = Instruction::executeAND(core);
        }
        else
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    }
    case 0b1100111: // JALR
    {
        // take param!!!
        inst_tp_ = JALR;
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = get_bits(static_cast<int32_t>(code) >> 20 , 11, 0);

        exec_status_ = Instruction::executeJALR(core);
        break;
    }
    case 0b1101111: // JAL
    {   
        inst_tp_ = JAL;
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));

        imm_ = (get_bits(code, 31, 31) << 20) + (get_bits(code, 30, 21) << 1) + (get_bits(code, 20, 20) << 11) + (get_bits(code, 19, 12) << 12);

        exec_status_ = Instruction::executeJAL(core);
        break;
    }
    case 0b01000011: // SB, SH, SW
    {   
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));

        imm_ = (get_bits(static_cast<int32_t>(code), 31, 25) << 5) + get_bits(code, 11, 7);
        auto funct3 = get_bits(code, 14, 12);

        if (funct3 == 0b000) // SB
        {   
            inst_tp_ = SB;
            exec_status_ = Instruction::executeSB(core);
        }
        else if (funct3 == 0b001) // SH
        {
            inst_tp_ = SH;
            exec_status_ = Instruction::executeSH(core);
        }
        else if (funct3 == 0b010) // SW
        {
            inst_tp_ = SW;
            exec_status_ = Instruction::executeSW(core);
        }
        else
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }
        
        break;
    }
    case 0b1100011:
    {
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));

        imm_ = (get_bits(code, 30, 25) << 5) + (get_bits(code, 11, 8) << 1) + (get_bits(code, 7, 7) << 11) + (get_bits(static_cast<int32_t>(code), 31, 31) << 12);

        auto funct3 = get_bits(code, 14, 12);
        if (funct3 == 0b000) // BEQ
        {
            inst_tp_ = BEQ;
            exec_status_ = executeBEQ(core);
        }
        else if (funct3 == 0b001) // BNE
        {
            inst_tp_ = BNE;
            exec_status_ = executeBEQ(core);
        }
        else if (funct3 == 0b100) // BLT
        {
            inst_tp_ = BLT;
            exec_status_ = executeBLT(core);
        } 
        else if (funct3 == 0b101) // BGE
        {
            inst_tp_ = BGE;
            exec_status_ = executeBGE(core);
        }
        else if (funct3 == 0b110) // BLTU
        {
            inst_tp_ = BLTU;
            exec_status_ = executeBLTU(core);
        }
        else if (funct3 == 0b111) // BGEU
        {
            inst_tp_ = BGEU;
            exec_status_ = executeBGEU(core);
        } 
        else 
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    default:
        std::cout << "no match with opcode = " << unsigned(type) << std::endl;
        exit(EXIT_FAILURE);

        break;
    }


};

/*  U-type  */
//-------------------------------------------//
bool Instruction::executeAUIPC(Core *core)
{
    core->SetReg(rd_, imm_ + core->GetPc());
    return true;
};

bool Instruction::executeLUI(Core *core)
{
    core->SetReg(rd_, imm_);
    return true;
};
//-------------------------------------------//


/*  I-type  */
//-------------------------------------------//
bool Instruction::executeADDI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) + imm_);
    return true;
};

bool Instruction::executeSLTI(Core *core)
{
    if (static_cast<int32_t>(core->GetReg(rs1_)) < static_cast<int32_t>(imm_))
    {
        core->SetReg(rd_, 1);
    }
    else
    {
        core->SetReg(rd_, 0);
    }
    return true;
};

bool Instruction::executeSLTIU(Core *core)
{
    if(core->GetReg(rs1_) < imm_)
    {
        core->SetReg(rd_, 1);
    }
    else
    {
        core->SetReg(rd_, 0);
    }
    return true;
};

bool Instruction::executeANDI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) & imm_);
    return true;
};

bool Instruction::executeORI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) | imm_);
    return true;
};

bool Instruction::executeXORI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) ^ imm_);
    return true;
};

bool Instruction::executeSLLI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) << imm_);
    return true;
};

bool Instruction::executeSRLI(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) >> imm_);
    return true;
};

bool Instruction::executeSRAI(Core *core)
{   
    if (get_bits(core->GetReg(rs1_), 31, 31) == 0b0) {
        core->SetReg(rd_, core->GetReg(rs1_) >> imm_);
    }
    else {
        core->SetReg(rd_, static_cast<uint32_t>(static_cast<int32_t>(core->GetReg(rs1_)) >> imm_));
    }
    return true;
};
//-------------------------------------------//

bool Instruction::executeADD(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) + core->GetReg(rs2_));
    return true;
};

bool Instruction::executeSLT(Core *core)
{
    if (static_cast<int32_t> (core->GetReg(rs1_)) < static_cast<int32_t> (core->GetReg(rs2_)))
    {
        core->SetReg(rd_, 1);
    }
    else
    {
        core->SetReg(rd_, 0);
    }
    return true;
};

bool Instruction::executeSLTU(Core *core)
{
    if (core->GetReg(rs1_) < core->GetReg(rs2_))
    {
        core->SetReg(rd_, 1);
    }
    else
    {
        core->SetReg(rd_, 0);
    }
    return true;
};

bool Instruction::executeXOR(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) ^ core->GetReg(rs2_));
    return true;

};

bool Instruction::executeOR(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) | core->GetReg(rs2_));
    return true;
};

bool Instruction::executeAND(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) & core->GetReg(rs2_));
    return true;
};

bool Instruction::executeSLL(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) << core->GetReg(rs2_));
    return true;
};

bool Instruction::executeSRL(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) >> core->GetReg(rs2_));
    return true;
};

bool Instruction::executeSUB(Core *core)
{
    core->SetReg(rd_, core->GetReg(rs1_) - core->GetReg(rs2_));
    return true;
};

bool Instruction::executeSRA(Core *core)
{
    if (get_bits(core->GetReg(rs1_), 31, 31) == 0b0)
    {
        core->SetReg(rd_, core->GetReg(rs1_) >> core->GetReg(rs2_));
    }
    else
    {
        core->SetReg(rd_, static_cast<uint32_t>(static_cast<int32_t>(core->GetReg(rs1_)) >> core->GetReg(rs2_)));
    }
    return true;
};

bool Instruction::executeJAL(Core *core) 
{
    core->SetReg(rd_, core->GetNextPc());
    core->branch(core->GetPc() + imm_);

    return true;
};

bool Instruction::executeJALR(Core *core)
{
    core->SetReg(rd_, core->GetNextPc());
    core->branch((core->GetReg(rs1_) + imm_ ) & (0xFFFFFFFE));

    return true;
};


bool Instruction::executeLB(Core *core) // ??????
{   
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 1);
    core->SetReg(rd_, value + (get_bits(value, 7, 7) == 0b1 ? 0xFFFFFF00 : 0)); 
    return true;
};

bool Instruction::executeLH(Core *core)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 2);
    core->SetReg(rd_, value + (get_bits(value, 15, 15) == 0b1 ? 0xFFFF0000 : 0));
    return true;
};

bool Instruction::executeLW(Core *core)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 4);
    core->SetReg(rd_, value);
    return true;
};

bool Instruction::executeLBU(Core *core)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 1);
    core->SetReg(rd_, value);
    return true;
};

bool Instruction::executeLHU(Core *core)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 2);
    core->SetReg(rd_, value);
    return true;
};

// S-type

bool Instruction::executeSB(Core *core)
{
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 1);
    return true;

};
bool Instruction::executeSH(Core *core)
{
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 2);
    return true;
};

bool Instruction::executeSW(Core *core)
{
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 4);
    return true;
};

bool Instruction::executeBEQ(Core * core)
{
    if (core->GetReg(rs1_) == core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_); 
    return true;
};

bool Instruction::executeBNE(Core * core)
{
    if (core->GetReg(rs1_) != core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_); 
    return true;
};

bool Instruction::executeBLT(Core * core)
{
    if (static_cast<int32_t>(core->GetReg(rs1_)) < static_cast<int32_t>(core->GetReg(rs2_)))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool Instruction::executeBGE(Core * core)
{
    if (static_cast<int32_t>(core->GetReg(rs1_)) >= static_cast<int32_t>(core->GetReg(rs2_)))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool Instruction::executeBLTU(Core * core)
{
    if (core->GetReg(rs1_) < core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool Instruction::executeBGEU(Core * core)
{
    if (core->GetReg(rs1_) >= core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_);
    return true;
};


uint32_t Instruction::get_bits(uint32_t code, size_t head, size_t tail)
{
    const size_t MAX_BITS_INSTR = 32;
    assert(head > tail);
    assert(MAX_BITS_INSTR > head);

    return ((code << (MAX_BITS_INSTR - head - 1)) >> (MAX_BITS_INSTR - head + tail - 1));
}

// template<int head, int tail, class T = uint32_t>
// T get_bits(T code)
// {
//     assert(head > tail);
//     return code << ((sizeof(T) * 8) - head - 1) >> (sizeof(T) * 8 - head + tail - 1);
// }
