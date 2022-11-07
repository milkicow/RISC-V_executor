#include "Core.hpp"


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