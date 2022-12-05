#include "header.hpp"
#include "dump_read.hpp"
#include "Memory.hpp"
#include "Core.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) { 
        std::cout << "num of args = " << argc << std::endl;
        exit(EXIT_FAILURE); 
    }
    std::string filename = argv[1];
    std::vector<std::string> stream;
    
    ClearFile("logfile.txt");
    
    std::ifstream file(filename, std::ios_base::in);
    stream = pars::read_str(file);
    file.close();

    Memory mem = {};
    pars::parsing(mem.GetMemAddr(), stream);
    mem.DumpMem();

    Core core(&mem);
    bool exe_status = core.execute(&mem);

    std::cout << "exe_status = " << exe_status << std::endl;
    
    return 0;
}
