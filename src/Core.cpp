#include "Execute.hpp"
#include "header.hpp"
#include "Core.hpp"
#include "Instruction.hpp"
#include "cache.hpp"

void Core::Dump() const
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

    lfu::cache<Instruction> cache(CACHE_SIZE);

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

        // std::cout << "PC = " << GetPc() << std::endl;
        // std::cout << "undecoded inst = " << std::hex << undecoded_inst << std::endl;

        SetNextPc(GetPc() + 4);


        bool (*execute[]) (Core * core, const Instruction * inst) = {
            executeLUI, executeAUIPC, 
            executeSLLI, executeSRLI, executeSRAI,
            executeADD, executeSLT, executeSLTU,
            executeAND, executeOR, executeXOR,
            executeSLL, executeSRL,
            executeSUB, executeSRA,
            executeADDI, executeSLTI, executeSLTIU,
            executeANDI, executeORI, executeXORI,
            executeJAL, executeJALR,
            executeLB, executeLH, executeLW, executeLBU, executeLHU,
            executeSB, executeSH, executeSW,
            executeBEQ, executeBNE, executeBLT, executeBGE, executeBLTU, executeBGEU
        };

        Instruction inst = cache.lookup_update(undecoded_inst, decode_instr);

        InstId inst_tp_ = inst.get_inst_tp_();
        std::cout << " on instruction " << InstIdName[inst_tp_] << " " << std::hex << undecoded_inst << std::endl;
        exe_status = execute[inst_tp_] (this, &inst);

        if (GetReg(R02) == 0x090000 && undecoded_inst == 0x00008067)
        {   
            std::cout << "END" << std::endl;
            exe_status = true;
            break;
        }

        inst.Dump();
        Dump();

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
