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

#include "libs.hpp"
#include "Memory.hpp"
#include "Core.hpp"
#include "Instruction.hpp"

void ClearFile(std::string filename);

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
