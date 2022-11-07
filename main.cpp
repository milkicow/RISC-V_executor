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
    std::vector<uint32_t>commands = pars::getcommands(stream);
    
    std::cout << "vector of commands: " << std::endl;
    for (auto ptr = commands.begin(); ptr != commands.end(); ++ptr) {
        
        std::cout << std::hex << *ptr << std::endl;
    }
    std::cout << std::endl;

    Core core = {};

    execute(commands, &core);

    return 0;
}
