#pragma once

#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <iomanip>

#define LOX printf("NORMALLY IN %s in %s in LINE = %d \n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
#undef LOX
#define LOX 

const size_t MEM_SIZE = 0x100000;
const size_t REGS_NUMBER = 32;
const size_t INSTRUCTION_SIZE = 4;
const size_t NUMBER_OF_INSTRUCTIONS = 37;

enum types
{
    R, I, S, B, U, J
};

enum RegId
{
    R00, R01, R02, R03, R04, R05, R06, R07, R08, R09, R0A, R0B, R0C, R0D, R0E, ROF,
    R10, R11, R12, R13, R14, R15, R16, R17, R18, R19, R1A, R1B, R1C, R1D, R1E, R1F,
    SP = 2
};

bool (*execute[NUMBER_OF_INSTRUCTIONS]) (Core * core, Instruction * instruction) = 
{
    executeLUI();
    executeAUIPC();

    executeSLLI();
    executeSRLI();
    executeSRAI();

    executeADD();
    executeSLT();
    executeSLTU();

    executeAND();
    executeOR();
    executeXOR();

    executeSLL();
    executeSRL();

    executeSUB();
    executeSRA();

    executeADDI();
    executeSLTI();
    executeSLTIU();

    executeANDI();
    executeORI();
    executeXORI();

    executeJAL();
    executeJALR();

    executeLB();
    executeLH();
    executeLW();
    executeLBU();
    executeLHU();

    executeSB();
    executeSH();
    executeSW();

    executeBEQ();
    executeBNE();
    executeBLT();
    executeBGE();
    executeBLTU();
    executeBGEU();
};
