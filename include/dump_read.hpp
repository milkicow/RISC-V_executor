#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>

#include <ctype.h>

namespace pars {

void delete_symbols(std::string& string);

std::vector<std::string> read_str(std::string filename) {

    std::fstream file(filename, std::ios_base::in);

    file.seekg(0, std::ios_base::end);
    size_t file_size = file.tellg();
    std::cout << "file_size = " << file_size << std::endl;
    file.seekg(0, std::ios_base::beg);
    assert(file_size != 0);

    std::vector<std::string> stream;

    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            //delete_symbols(line);
            stream.push_back(line);
        }
    }

    file.close();
    return stream;
}

void delete_symbols(std::string& string) {
    for (auto ptr = string.begin(); ptr != string.end(); ++ptr) {
        while(*ptr == ' ' || *ptr == '\t') {
            string.erase(ptr);
        }
    }
}

std::vector<char> read(std::string filename) {

    std::fstream file(filename, std::ios_base::binary | std::ios_base::in);
   
    file.seekg(0, std::ios_base::end);
    size_t file_size = file.tellg();
    //std::cout << "file_size = " << file_size << std::endl;
    file.seekg(0, std::ios_base::beg);

    std::vector<char> stream (file_size, 0);
    file.read(stream.data(), file_size);

    file.close();
    return stream;
}

void correct_file(std::vector<std::string> stream) {
    std::string correct_type = "test_prog.out:     file format elf32-littleriscv";
    std::string in_str = *stream.begin();

    if (correct_type != *stream.begin()) {
         
        std::cout << "TYPE OF THE FILE IS NOT CORRECT!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool find(std::string find, std::string source) {
    for(auto find_ptr = find.begin(); find_ptr != find.end(); ++find_ptr) {
        bool status = false;
        for (auto candidate = source.begin(); candidate != source.end(); ++candidate) {
            if (*find_ptr == *candidate) status = true;
        }
        if (status == false) return false;
    }
    return true;
}

std::vector<uint32_t> getcommands(std::vector<std::string>& stream) {

    std::fstream log_file("logfile.txt", std::ios_base::app);
     
    correct_file(stream);
     
    auto stream_ptr = stream.begin();
    
    while (!find("<>", *stream_ptr)) ++stream_ptr;
    ++stream_ptr;    
    
     

    std::vector<uint32_t> commands;
    int address;
    char separation;
    uint32_t command;
    
    while (stream_ptr != stream.end()) {
         
        std::stringstream ss(*stream_ptr);

        ss >> std::hex >> std::noshowbase >> address >> separation >> std::hex >> std::noshowbase >> command;
        commands.push_back(command);

        log_file << "was read: adress =  " << std::hex << address << " separation = " << separation << " command = " << std::hex << command << std::endl;

        ++stream_ptr;
    }
    log_file << std::endl;
    
    log_file.close();
    return commands;
}

unsigned char turn_into_number(char num)
{
    assert(isdigit(num) || num >= 'a' && num <= 'f');

    return (isdigit(num)) ? (num - '0') : (num - 'a' + 10);
}

void parsing(char * mem_, std::vector<std::string>& stream)
{   
    std::fstream log_file("logfile.txt", std::ios_base::app);
     
    //correct_file(stream);
     
    auto stream_ptr = stream.begin();
    
    while (!find("<>", *stream_ptr)) ++stream_ptr;
    ++stream_ptr; 

    char ch;
    int mem_ptr = 0;
    std::string str;
    while (stream_ptr != stream.end())
    {   
        str = *stream_ptr;
        auto str_ptr = str.begin();

        for (; *str_ptr != ':'; ++str_ptr) {}
        ++str_ptr;
        while ((*str_ptr == ' ' || *str_ptr == '\t')) 
        {   
            ++str_ptr;
        }

        if (str_ptr != str.end()) 
        {
            for (int i = 0; i != 4; ++i)
            {   
                mem_[mem_ptr + 3 - i] = (turn_into_number(str_ptr[0]) << 4) + turn_into_number(str_ptr[1]);

                str_ptr += 2;
            }
            mem_ptr += 4;
        }
        ++stream_ptr;
    }

}

}
