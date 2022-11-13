#include "header.hpp"
#include "dump_read.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) { 
        std::cout << "num of args = " << argc << std::endl;
        exit(EXIT_FAILURE); 
    }
    std::string filename = argv[1];
    std::vector<std::string> stream;
    
    ClearFile("logfile.txt");
    

    stream = pars::read_str(filename);
    // std::vector<uint32_t>commands = pars::getcommands(stream);

    /* Load in memory */
    Memory mem = {};

    pars::parsing(mem.GetMemAddr(), stream);
    // auto mem_addr = 0;
    // auto commands_ptr = commands.begin();
    // while (commands_ptr != commands.end())
    // {
    //     mem.write(mem_addr, *commands_ptr, 4);// неправильно

    //     mem_addr += 4;
    //     commands_ptr++;
    // }
    
    mem.DumpMem();
    // uint32_t value = 0x00112e23;
    // mem.write(0, value, 4);
    // mem.DumpMem();

    Core core(&mem);
    bool exe_status = execute(&mem, &core);

    std::cout << "exe_status = " << exe_status << std::endl;
    
    // int place = 196563;
    // for (int i = 0; i < 4; ++i)
    // {   
    //     std::cout << unsigned(mem.mem_[place]) << std::endl;
    //     ++place;
    // }
    // std::cout << "vector of commands: " << std::endl;
    // for (auto ptr = commands.begin(); ptr != commands.end(); ++ptr) {
        
    //     std::cout << std::hex << *ptr << std::endl;
    // }
    // std::cout << std::endl;

    // Core core = {};
    // execute(commands, &core);

    return 0;
}
