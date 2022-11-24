#ifndef HEADER_H
#define HEADER_H

#include "libs.hpp"

void ClearFile(std::string filename)
{
    std::fstream file(filename, std::ios_base::out);
    file.close();
}

uint32_t get_bits(uint32_t code, size_t head, size_t tail)
{
    const size_t MAX_BITS_INSTR = 32;
    assert(head >= tail);
    assert(MAX_BITS_INSTR > head);

    return ((code << (MAX_BITS_INSTR - head - 1)) >> (MAX_BITS_INSTR - head + tail - 1));
}

/*  U-type  */
//-------------------------------------------//
bool executeAUIPC(Core * core, Instruction * instr)
{
    core->SetReg(rd_, imm_ + core->GetPc());
    return true;
};

bool executeLUI(Core * core, Instruction * instr)
{
    core->SetReg(rd_, imm_);
    return true;
};
//-------------------------------------------//


/*  I-type  */
//-------------------------------------------//
bool executeADDI(Core * core, Instruction * instr)
{   
    // std::cout << "before addi:\n";
    // std::cout << "rs1_ = " << rs1_ << " imm_ " << signed(imm_) << " rd_ = " << rd_ << std::endl;
    core->SetReg(rd_, core->GetReg(rs1_) + imm_);

    // std::cout << "after addi:\n";
    // std::cout << "reg[rd_] = " << core->GetReg(rd_) << std::endl << std::endl; 
    return true;
};

bool executeSLTI(Core * core, Instruction * instr)
{   
    //std::cout << "SLTI\n";
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

bool executeSLTIU(Core * core, Instruction * instr)
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

bool executeANDI(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) & imm_);
    return true;
};

bool executeORI(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) | imm_);
    return true;
};

bool executeXORI(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) ^ imm_);
    return true;
};

bool executeSLLI(Core * core, Instruction * instr)
{   
    // std::cout << "SLLI\n";
    core->SetReg(rd_, core->GetReg(rs1_) << imm_);
    return true;
};

bool executeSRLI(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) >> imm_);
    return true;
};

bool executeSRAI(Core * core, Instruction * instr)
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

bool executeADD(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) + core->GetReg(rs2_));
    return true;
};

bool executeSLT(Core * core, Instruction * instr)
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

bool executeSLTU(Core * core, Instruction * instr)
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

bool executeXOR(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) ^ core->GetReg(rs2_));
    return true;

};

bool executeOR(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) | core->GetReg(rs2_));
    return true;
};

bool executeAND(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) & core->GetReg(rs2_));
    return true;
};

bool executeSLL(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) << core->GetReg(rs2_));
    return true;
};

bool executeSRL(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) >> core->GetReg(rs2_));
    return true;
};

bool executeSUB(Core * core, Instruction * instr)
{
    core->SetReg(rd_, core->GetReg(rs1_) - core->GetReg(rs2_));
    return true;
};

bool executeSRA(Core * core, Instruction * instr)
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

bool executeJAL(Core * core, Instruction * instr) 
{
    core->SetReg(rd_, core->GetPc() + INSTRUCTION_SIZE);
    core->branch(core->GetPc() + imm_);
    return true;
};

bool executeJALR(Core * core, Instruction * instr)
{   
    // std::cout << "before: " << std::endl;
    // std::cout << "pc_ = " << core->GetPc() << " imm_ = " << imm_ << std::endl;
    // std::cout << "next_pc_ = " << core->GetNextPc() << std::endl;
    core->SetReg(rd_, core->GetPc() + INSTRUCTION_SIZE);
    core->branch((core->GetReg(rs1_) + imm_ ) & (0xFFFFFFFE));
    // std::cout << "after: " << std::endl;
    // std::cout << "pc_ = " << core->GetPc() << " imm_ = " << imm_ << std::endl;
    // std::cout << "next_pc_ = " << core->GetNextPc() << std::endl;

    return true;
};

bool executeLB(Core * core, Instruction * instr) 
{   
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 1);
    core->SetReg(rd_, value + (get_bits(value, 7, 7) == 0b1 ? 0xFFFFFF00 : 0)); 
    return true;
};

bool executeLH(Core * core, Instruction * instr)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 2);
    core->SetReg(rd_, value + (get_bits(value, 15, 15) == 0b1 ? 0xFFFF0000 : 0));
    return true;
};

bool executeLW(Core * core, Instruction * instr)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 4);
    core->SetReg(rd_, value);
    return true;
};

bool executeLBU(Core * core, Instruction * instr)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 1);
    core->SetReg(rd_, value);
    return true;
};

bool executeLHU(Core * core, Instruction * instr)
{
    uint32_t value;
    core->read(core->GetReg(rs1_) + imm_, &value, 2);
    core->SetReg(rd_, value);
    return true;
};

// S-type

bool executeSB(Core * core, Instruction * instr)
{
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 1);
    return true;

};
bool executeSH(Core * core, Instruction * instr)
{
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 2);
    return true;
};

bool executeSW(Core * core, Instruction * instr)
{
     
    // std::cout << "rs1_ = " << rs1_ << " rs2_ = " << rs2_ << " imm_ = " << imm_ << std::endl;
    // std::cout << "core->GetReg(rs1_) = " << core->GetReg(rs1_) << std::endl;
    core->write(core->GetReg(rs1_) + imm_, core->GetReg(rs2_), 4);
     
    return true;
};

bool executeBEQ(Core * core, Instruction * instr)
{
    if (core->GetReg(rs1_) == core->GetReg(rs2_))
    {
        //std::cout << core->GetReg(rs1_) << "==" << core->GetReg(rs2_) << std::endl;
        core->branch(core->GetPc() + imm_); 
    }
    return true;
};

bool executeBNE(Core * core, Instruction * instr)
{
    if (core->GetReg(rs1_) != core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_); 
    return true;
};

bool executeBLT(Core * core, Instruction * instr)
{
    if (static_cast<int32_t>(core->GetReg(rs1_)) < static_cast<int32_t>(core->GetReg(rs2_)))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool executeBGE(Core * core, Instruction * instr)
{
    if (static_cast<int32_t>(core->GetReg(rs1_)) >= static_cast<int32_t>(core->GetReg(rs2_)))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool executeBLTU(Core * core, Instruction * instr)
{
    if (core->GetReg(rs1_) < core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_);
    return true;
};

bool executeBGEU(Core * core, Instruction * instr)
{
    if (core->GetReg(rs1_) >= core->GetReg(rs2_))
        core->branch(core->GetPc() + imm_);
    return true;
};

#endif