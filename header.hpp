/* -----------------------------------------  TO DO: ----------------------------------------- */
    // do many exefunctions!!!
    // do normal debug vv not bad 
    // do func to work with memory: read and write for branch load and store as i conserned !!! !!!



    // maybe do something without "memory" - char vector, 
    //but with std::vector<uint32_t> and pointer on elem pc ( next_pc = 4 + pc ---> ++pc) 


    //      FIRST OF ALL:  REWRITE GET BITS FUNCTION!!!! // work properly vv


    // NEXT STEP:
    // do func to work with memory: read and write for branch load and store as i conserned !!! !!!
    // signed / unsigned numbers + in dmp: why imm_ is unsigned?? lol however it wiil work if i cast it to sign in other commands normally i think no?

    // separate on many headers like Core, Instruction and mb + Hardware
/* ----------------------------------------- -------- -----------------------------------------*/

#pragma once

#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <iomanip>

#define LOX printf("NORMALLY IN %s in %s in LINE = %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
#undef LOX
#define LOX 

void ClearFile(std::string filename);

enum types
{
    R, I, S, B, U, J
};

enum RegId
{
    R00, R01, R02, R03, R04, R05, R06, R07, R08, R09, R0A, R0B, R0C, R0D, R0E, ROF,
    R10, R11, R12, R13, R14, R15, R16, R17, R18, R19, R1A, R1B, R1C, R1D, R1E, R1F
};

uint32_t get_bits(uint32_t code, size_t head, size_t tail)
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

const size_t MEM_SIZE = 8192 * 32;
const size_t REGS_NUMBER = 32;
const size_t InstructionSize = 1;

class Memory final
{
private:
    char mem_[MEM_SIZE] = {};

public:

    bool write (uint32_t addr, uint32_t value, size_t size);
    bool read (uint32_t addr,  uint32_t * value, size_t size);
};

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
}



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
        ERROR

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
        "ERROR"
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
            /* !!!TO DO:!!! */
    bool executeBRANCH(Core *core);
    bool executeLOAD(Core *core);
    bool executeSTORE(Core *core);

public:

    void Dump()
    {   
        std::fstream log_file("logfile.txt", std::ios_base::app);
        log_file << "instruction " << InstIdName[inst_tp_] << " : "<< std::endl;
        log_file << " rd_ = " << rd_ << " rs1_ = " << rs1_ << " rs2_ = " << rs2_ << std::endl;
        log_file << " imm_ = " << imm_ << std::endl;
        log_file.close();
    }
    Instruction(Core *core, uint32_t code);
    bool GetExexStatus() { return exec_status_; }

    /* execute sth */

};

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

void execute(std::vector<uint32_t> commands, Core *core)
{   
    bool status = true;

    while (status)
    {   
        Instruction inst (core, commands[core->GetPc()]);
        inst.Dump();
        status = inst.GetExexStatus();
    
        core->IncPc();
        core->SetReg(R00, 0); // must equal 0

        core->Dump();
    }
}

void ClearFile(std::string filename)
{
    std::fstream file(filename, std::ios_base::out);
    file.close();
}


// class memory
// {
//     using data_t = char;
//     std::vector<data_t> data_;
//     size_t size_;

// public:
//     memory(size_t size) : data_(size, 0) {}
//     size_t size() const { return size_; }

//     data_t* data() { return data_.data (); }

//     using status = bool;
//     status load_mem(const char * binfile)
//     {
//         //std::cout << binfile << "\n";
//         LOX
//         std::ifstream binary (binfile, std::ios_base::in);
//         LOX

//         binary.seekg(0, std::ios_base::end);
//         LOX
//         size_t file_size = binary.tellg();
//         LOX
//         binary.seekg(0, std::ios_base::beg);
//         LOX

//         if(file_size > size())
//         {
//             LOX
//             return false; //FILE > CAPACITY too huge
//         }

//         LOX
//         binary.read(data_.data(), file_size);
//         LOX
//         binary.close();
//         return true;
//     }
// };
