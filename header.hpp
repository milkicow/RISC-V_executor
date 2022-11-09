/* -----------------------------------------  TO DO: ----------------------------------------- */
    // do many exefunctions!!!
    // do normal debug vv: not bad 
    // do func to work with memory: read and write for branch load and store as i conserned !!! !!! v



    // maybe do something without "memory" - char vector, 
    //but with std::vector<uint32_t> and pointer on elem pc ( next_pc = 4 + pc ---> ++pc) 


    //      FIRST OF ALL:  REWRITE GET BITS FUNCTION!!!! // work properly vv


    // NEXT STEP:
    // do func to work with memory: read and write for branch load and store as i conserned !!! !!! vv NO TEST - LACK OF MEMORY :))
    // signed / unsigned numbers + in dmp: why imm_ is unsigned?? lol however it wiil work if i cast it to sign in other commands normally i think no?

    // separate on many headers like Core, Instruction and mb + Hardware vv


    // need to do:
    // char memory + normal exe function + test functions + work with addresses

    // do normal dirs and cmake
    // check how jump func works ( by bits )

    // now segfault on mem.write() check it 
/* ----------------------------------------- -------- -----------------------------------------*/

#include "libs.hpp"
#include "Memory.hpp"
#include "Core.hpp"
#include "Instruction.hpp"

void ClearFile(std::string filename);

// void execute(std::vector<uint32_t> commands, Core *core)
// {   
//     bool status = true;

//     while (status)
//     {   
//         Instruction inst (core, commands[core->GetPc()]);
//         inst.Dump();
//         core->Dump();
//         status = inst.GetExexStatus();
    
//         core->IncPc();
//         core->SetReg(R00, 0); // must equal 0

    
//     }
// }

bool execute(Memory * mem, Core * core)
{
    bool status = true;
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

        std::cout << "PC = " << core->GetPc() << std::endl;
        std::cout << "undecoded inst = " << std::hex << undecoded_inst << std::endl;

        //printf("mem_ addr = %p\n", mem->GetMemAddr());
        //std::cout << "mem_ addr = " << mem->GetMemAddr() << std::endl;
        //std::cout << "undecoded inst addr = " << &undecoded_inst << std::endl;
        //std::cout << "mem[core->GetPc()] = " << mem->mem_[core->GetPc()] << std::endl;
        //printf("&mem[core->GetPc()] = %p \n", &mem[core->GetPc()]);

        LOX
        core->SetNextPc(core->GetPc() + 4);
        LOX
        Instruction inst(core, undecoded_inst);
        LOX

        if (inst.GetExexStatus() == false)
        {
            std::cout << "EXECUTION WAS FAILED!!! \n";
            status = false;
            break;
        }

        core->SetPc(core->GetNextPc());
        core->SetReg(R00, 0);
    }

    return status;
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
