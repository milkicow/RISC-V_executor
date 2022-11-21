#include "Core.hpp"
#include "Instruction.hpp"


void Core::Dump() 
{
    std::fstream log_file("logfile.txt", std::ios_base::app);
    log_file << "*--------------------------------------------------* \n";
    log_file << " pc = " << GetPc() << " next_pc = " << GetNextPc() << std::endl;

    for (int i = 0; i < REGS_NUMBER ; i++) {
        log_file << "REG_" << std::setw( 2 ) << std::setfill( '0' ) << i << " = " << signed(regs_[i]) << std::endl;
    }

    log_file << "*--------------------------------------------------* \n\n";
    log_file.close();
}

bool Core::execute(Memory * mem)
{
    bool status = true;
    bool exe_status = false;

    SetReg(SP, 0x090000); 
    while (status)
    {
        uint32_t undecoded_inst;

        if (!mem->read(GetPc(), &undecoded_inst, 4)) 
        {
            status = false;
            break;
        }
        if (undecoded_inst == 0) 
        {
            status = false;
            break;
        }

        std::cout << "PC = " << GetPc() << std::endl;
        std::cout << "undecoded inst = " << std::hex << undecoded_inst << std::endl;

        SetNextPc(GetPc() + 4);
        Instruction inst(this, undecoded_inst);

        if (GetReg(R02) == 0x090000 && undecoded_inst == 0x00008067)
        {   
            std::cout << "END" << std::endl;
            exe_status = true;
            break;
        }

        inst.Dump();
        Dump();

        exe_status = inst.GetExexStatus();
        if (exe_status == false)
        {
            std::cout << "EXECUTION WAS FAILED!!! \n";
            status = false;
            break;
        }

        SetPc(GetNextPc());
        SetReg(R00, 0);
    }

    return exe_status;
}