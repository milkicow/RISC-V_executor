#include "header.hpp"
#include "Execute.hpp"
#include "Core.hpp"
#include "Instruction.hpp"


/*  U-type  */
//-------------------------------------------//
bool executeAUIPC(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), inst->get_imm_() + core->GetPc());
    return true;
};

bool executeLUI(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), inst->get_imm_());
    return true;
};
//-------------------------------------------//


/*  I-type  */
//-------------------------------------------//
bool executeADDI(Core * core, const Instruction * inst)
{   
    // std::cout << "before addi:\n";
    // std::cout << "inst->get_rs1_() = " << inst->get_rs1_() << " inst->get_imm_() " << signed(inst->get_imm_()) << " inst->get_rd_() = " << inst->get_rd_() << std::endl;
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) + inst->get_imm_());

    // std::cout << "after addi:\n";
    // std::cout << "reg[inst->get_rd_()] = " << core->GetReg(inst->get_rd_()) << std::endl << std::endl; 
    return true;
};

bool executeSLTI(Core * core, const Instruction * inst)
{   
    //std::cout << "SLTI\n";
    if (static_cast<int32_t>(core->GetReg(inst->get_rs1_())) < static_cast<int32_t>(inst->get_imm_()))
    {
        core->SetReg(inst->get_rd_(), 1);
    }
    else
    {
        core->SetReg(inst->get_rd_(), 0);
    }
    return true;
};

bool executeSLTIU(Core * core, const Instruction * inst)
{
    if(core->GetReg(inst->get_rs1_()) < inst->get_imm_())
    {
        core->SetReg(inst->get_rd_(), 1);
    }
    else
    {
        core->SetReg(inst->get_rd_(), 0);
    }
    return true;
};

bool executeANDI(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) & inst->get_imm_());
    return true;
};

bool executeORI(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) | inst->get_imm_());
    return true;
};

bool executeXORI(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) ^ inst->get_imm_());
    return true;
};

bool executeSLLI(Core * core, const Instruction * inst)
{   
    // std::cout << "SLLI\n";
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) << inst->get_imm_());
    return true;
};

bool executeSRLI(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) >> inst->get_imm_());
    return true;
};

bool executeSRAI(Core * core, const Instruction * inst)
{   
    if (get_bits(core->GetReg(inst->get_rs1_()), 31, 31) == 0b0) {
        core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) >> inst->get_imm_());
    }
    else {
        core->SetReg(inst->get_rd_(), static_cast<uint32_t>(static_cast<int32_t>(core->GetReg(inst->get_rs1_())) >> inst->get_imm_()));
    }
    return true;
};
//-------------------------------------------//

bool executeADD(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) + core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeSLT(Core * core, const Instruction * inst)
{
    if (static_cast<int32_t> (core->GetReg(inst->get_rs1_())) < static_cast<int32_t> (core->GetReg(inst->get_rs2_())))
    {
        core->SetReg(inst->get_rd_(), 1);
    }
    else
    {
        core->SetReg(inst->get_rd_(), 0);
    }
    return true;
};

bool executeSLTU(Core * core, const Instruction * inst)
{
    if (core->GetReg(inst->get_rs1_()) < core->GetReg(inst->get_rs2_()))
    {
        core->SetReg(inst->get_rd_(), 1);
    }
    else
    {
        core->SetReg(inst->get_rd_(), 0);
    }
    return true;
};

bool executeXOR(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) ^ core->GetReg(inst->get_rs2_()));
    return true;

};

bool executeOR(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) | core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeAND(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) & core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeSLL(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) << core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeSRL(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) >> core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeSUB(Core * core, const Instruction * inst)
{
    core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) - core->GetReg(inst->get_rs2_()));
    return true;
};

bool executeSRA(Core * core, const Instruction * inst)
{
    if (get_bits(core->GetReg(inst->get_rs1_()), 31, 31) == 0b0)
    {
        core->SetReg(inst->get_rd_(), core->GetReg(inst->get_rs1_()) >> core->GetReg(inst->get_rs2_()));
    }
    else
    {
        core->SetReg(inst->get_rd_(), static_cast<uint32_t>(static_cast<int32_t>(core->GetReg(inst->get_rs1_())) >> core->GetReg(inst->get_rs2_())));
    }
    return true;
};

bool executeJAL(Core * core, const Instruction * inst) 
{
    core->SetReg(inst->get_rd_(), core->GetPc() + INSTRUCTION_SIZE);
    core->branch(core->GetPc() + inst->get_imm_());
    return true;
};

bool executeJALR(Core * core, const Instruction * inst)
{   
    // std::cout << "before: " << std::endl;
    // std::cout << "pc_ = " << core->GetPc() << " inst->get_imm_() = " << inst->get_imm_() << std::endl;
    // std::cout << "next_pc_ = " << core->GetNextPc() << std::endl;
    core->SetReg(inst->get_rd_(), core->GetPc() + INSTRUCTION_SIZE);
    core->branch((core->GetReg(inst->get_rs1_()) + inst->get_imm_() ) & (0xFFFFFFFE));
    // std::cout << "after: " << std::endl;
    // std::cout << "pc_ = " << core->GetPc() << " inst->get_imm_() = " << inst->get_imm_() << std::endl;
    // std::cout << "next_pc_ = " << core->GetNextPc() << std::endl;

    return true;
};


bool executeLB(Core * core, const Instruction * inst) // ??????
{   
    uint32_t value;
    core->read(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), &value, 1);
    core->SetReg(inst->get_rd_(), value + (get_bits(value, 7, 7) == 0b1 ? 0xFFFFFF00 : 0)); 
    return true;
};

bool executeLH(Core * core, const Instruction * inst)
{
    uint32_t value;
    core->read(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), &value, 2);
    core->SetReg(inst->get_rd_(), value + (get_bits(value, 15, 15) == 0b1 ? 0xFFFF0000 : 0));
    return true;
};

bool executeLW(Core * core, const Instruction * inst)
{
    uint32_t value;
    core->read(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), &value, 4);
    core->SetReg(inst->get_rd_(), value);
    return true;
};

bool executeLBU(Core * core, const Instruction * inst)
{
    uint32_t value;
    core->read(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), &value, 1);
    core->SetReg(inst->get_rd_(), value);
    return true;
};

bool executeLHU(Core * core, const Instruction * inst)
{
    uint32_t value;
    core->read(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), &value, 2);
    core->SetReg(inst->get_rd_(), value);
    return true;
};

// S-type

bool executeSB(Core * core, const Instruction * inst)
{
    core->write(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), core->GetReg(inst->get_rs2_()), 1);
    return true;

};
bool executeSH(Core * core, const Instruction * inst)
{
    core->write(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), core->GetReg(inst->get_rs2_()), 2);
    return true;
};

bool executeSW(Core * core, const Instruction * inst)
{
     
    // std::cout << "inst->get_rs1_() = " << inst->get_rs1_() << " inst->get_rs2_() = " << inst->get_rs2_() << " inst->get_imm_() = " << inst->get_imm_() << std::endl;
    // std::cout << "core->GetReg(inst->get_rs1_()) = " << core->GetReg(inst->get_rs1_()) << std::endl;
    core->write(core->GetReg(inst->get_rs1_()) + inst->get_imm_(), core->GetReg(inst->get_rs2_()), 4);
     
    return true;
};

bool executeBEQ(Core * core, const Instruction * inst)
{
    if (core->GetReg(inst->get_rs1_()) == core->GetReg(inst->get_rs2_()))
    {
        //std::cout << core->GetReg(inst->get_rs1_()) << "==" << core->GetReg(inst->get_rs2_()) << std::endl;
        core->branch(core->GetPc() + inst->get_imm_()); 
    }
    return true;
};

bool executeBNE(Core * core, const Instruction * inst)
{
    if (core->GetReg(inst->get_rs1_()) != core->GetReg(inst->get_rs2_()))
        core->branch(core->GetPc() + inst->get_imm_()); 
    return true;
};

bool executeBLT(Core * core, const Instruction * inst)
{
    if (static_cast<int32_t>(core->GetReg(inst->get_rs1_())) < static_cast<int32_t>(core->GetReg(inst->get_rs2_())))
        core->branch(core->GetPc() + inst->get_imm_());
    return true;
};

bool executeBGE(Core * core, const Instruction * inst)
{
    if (static_cast<int32_t>(core->GetReg(inst->get_rs1_())) >= static_cast<int32_t>(core->GetReg(inst->get_rs2_())))
        core->branch(core->GetPc() + inst->get_imm_());
    return true;
};

bool executeBLTU(Core * core, const Instruction * inst)
{
    if (core->GetReg(inst->get_rs1_()) < core->GetReg(inst->get_rs2_()))
        core->branch(core->GetPc() + inst->get_imm_());
    return true;
};

bool executeBGEU(Core * core, const Instruction * inst)
{
    if (core->GetReg(inst->get_rs1_()) >= core->GetReg(inst->get_rs2_()))
        core->branch(core->GetPc() + inst->get_imm_());
    return true;
};