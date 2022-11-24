#include "libs.hpp"
#include "Memory.hpp"
#include "Core.hpp"
#include "Instruction.hpp"

void ClearFile(std::string filename)
{
    std::fstream file(filename, std::ios_base::out);
    file.close();
}