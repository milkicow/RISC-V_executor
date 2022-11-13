#include "libs.hpp"
#include "Memory.hpp"
#include "Core.hpp"
#include "Instruction.hpp"

void ClearFile(std::string filename);

bool execute(Memory * mem, Core * core)
{
    bool status = true;
    bool exe_status = false;

    core->SetReg(SP, 8192 * 24 - 21); 
    while (status)
    {
        uint32_t undecoded_inst;

        if (!mem->read(core->GetPc(), &undecoded_inst, 4)) 
        {
            status = false;
            break;
        }
        if (undecoded_inst == 0) 
        {
            status = false;
            break;
        }
        if (undecoded_inst == 0x00000001)
        {   
            std::cout << "END" << std::endl;
            exe_status = true;
            break;
        }

        std::cout << "PC = " << core->GetPc() << std::endl;
        std::cout << "undecoded inst = " << std::hex << undecoded_inst << std::endl;

        core->SetNextPc(core->GetPc() + 4);
        Instruction inst(core, undecoded_inst);

        inst.Dump();
        core->Dump();

        exe_status = inst.GetExexStatus();
        if (exe_status == false)
        {
            std::cout << "EXECUTION WAS FAILED!!! \n";
            status = false;
            break;
        }

        core->SetPc(core->GetNextPc());
        core->SetReg(R00, 0);
    }

    return exe_status;
}

void ClearFile(std::string filename)
{
    std::fstream file(filename, std::ios_base::out);
    file.close();
}
