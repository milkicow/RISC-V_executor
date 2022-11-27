#include "header.hpp"
#include "Instruction.hpp"


Instruction::Instruction(uint32_t code)
{
    inst_tp_ = ERROR;
    uint32_t type = code & 0x7F;

    //std::cout << "code = "; 
    //dump_bits(code, 31, 25); std::cout << " "; dump_bits(code, 24, 20); std::cout << " "; dump_bits(code, 19, 15); std::cout << " "; dump_bits(code, 14, 12); std::cout << " "; dump_bits(code, 11, 7); std::cout << " "; dump_bits(code, 6, 0); std::cout << std::endl;

    switch (type)
    {
    case 0:
    {   
        break;
    }
    case 0b0000011: // I-type 
    {
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = get_bits((static_cast<int32_t>(code) >> 20), 31, 0);
        
        auto funct3 = get_bits(code, 14, 12);

        switch (funct3)
        {
            case 0b000: // LB
            {
                inst_tp_ = LB;
                break;
            }
            case 0b001: // LH
            {
                inst_tp_ = LH;
                break;
            }
            case 0b010: // LW
            {
                inst_tp_ = LW;
                break;
            }
            case 0b100: // LBU
            {
                inst_tp_ = LBU;
                break;
            }
            case 0b101: // LHU
            {
                inst_tp_ = LHU;
                break;
            }
            default:
            {
                std::cout << "no match with command = " << code << std::endl;
                exit(EXIT_FAILURE);
            }

        }
        break;
    }
    case 0b0010111: // U-type AUIPC
    {
        imm_ = get_bits(code, 31, 12);
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));

        //std::cout << "rd_ = " << rd_ << " imm_ = " << imm_ << std::endl;
        
        inst_tp_ = AUIPC;
        break;
    }
    case 0b0110111: // U-type LUI
    {
        imm_ = get_bits(code, 31, 12);
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));

        //std::cout << "rd_ = " << rd_ << " imm_ = " << imm_ << std::endl;

        inst_tp_ = LUI;
        break;
    }
    case 0b0010011: // I-type 
    {   
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = get_bits((static_cast<int32_t>(code) >> 20), 31, 0);
        
        // std::cout << "dump_bits = ";
        // dump_bits(imm_, 31, 0);
        //std::cout << std::endl;
        
        auto funct3 = get_bits(code, 14, 12);
        auto funct7 = get_bits(imm_, 11, 5);


        switch (funct3)
        {
            case 0b000: // ADDI
            {
                inst_tp_ = ADDI;
                break;
            }
            case 0b010: // SLTI
            {
                inst_tp_ = SLTI;
                break;
            }
            case 0b011: // SLTIU
            {
                inst_tp_ = SLTIU;
                break;
            }
            case 0b111: // ANDI
            {
                inst_tp_ = ANDI;
                break;
            }
            case 0b110: // ORI
            {
                inst_tp_ = ORI;
                break;
            }
            case 0b100: // XORI
            {
                inst_tp_ = XORI;
                break;
            }
            case 0b001: // SLLI
            {
                if (funct7 == 0b0000000)
                {
                    inst_tp_ = SLLI;
                }
                else 
                {
                    std::cout << "no match with command = " << code << "funct7 = " << funct7 << " funct3 = " << funct3 << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 0b101:
            {
                if      (funct7 == 0b0000000) inst_tp_ = SRLI;
                else if (funct7 == 0b0100000) inst_tp_ = SRAI;
                else
                {
                    std::cout << "no match with command = " << code << "funct7 = " << funct7 << " funct3 = " << funct3 << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default:
            {
                std::cout << "no match with command = " << code << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    case 0b0110011: // R-type
    {
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));


        auto funct3 = get_bits(code, 14, 12);
        auto funct7 = get_bits(code, 31, 25);

        if      (funct3 == 0b000 && funct7 == 0b0000000) inst_tp_ = ADD;
        else if (funct3 == 0b000 && funct7 == 0b0100000) inst_tp_ = SUB;
        else if (funct3 == 0b001 && funct7 == 0b0000000) inst_tp_ = SLL;
        else if (funct3 == 0b010 && funct7 == 0b0000000) inst_tp_ = SLT;
        else if (funct3 == 0b011 && funct7 == 0b0000000) inst_tp_ = SLTU;
        else if (funct3 == 0b100 && funct7 == 0b0000000) inst_tp_ = XOR;
        else if (funct3 == 0b101 && funct7 == 0b0000000) inst_tp_ = SRL;
        else if (funct3 == 0b101 && funct7 == 0b0100000) inst_tp_ = SRA;
        else if (funct3 == 0b110 && funct7 == 0b0000000) inst_tp_ = OR;
        else if (funct3 == 0b111 && funct7 == 0b0000000) inst_tp_ = AND;
        else
        {
            std::cout << "no match with command = " << code << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    }
    case 0b1100111: // JALR
    {
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        imm_ = get_bits(static_cast<int32_t>(code) >> 20 , 11, 0);
        auto funct3 = get_bits(code, 14, 12);

        if(funct3 == 0b000) inst_tp_ = JALR;
        break;
    }
    case 0b1101111: // JAL
    {   
        rd_ = static_cast<RegId> (get_bits(code, 11, 7));
        imm_ = (get_bits((static_cast<int32_t>(code) >> 31), 31, 0) << 20) + (get_bits(code, 30, 21) << 1) + (get_bits(code, 20, 20) << 11) + (get_bits(code, 19, 12) << 12);
        inst_tp_ = JAL;

        break;
    }
    case 0b00100011: // SB, SH, SW
    {   
         
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));

        imm_ = (get_bits((static_cast<int32_t>(code) >> 25), 31, 0) << 5) + get_bits(code, 11, 7);

        auto funct3 = get_bits(code, 14, 12);

        switch (funct3)
        {
            case 0b000: // SB
            {
                inst_tp_ = SB;
                break;
            }
            case 0b001: // SH
            {
                inst_tp_ = SH;
                break;
            }
            case 0b010: // SW
            {
                inst_tp_ = SW;
                break;
            }
            default:
            {
                std::cout << "no match with command = " << code << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    case 0b1100011:
    {
        rs1_ = static_cast<RegId> (get_bits(code, 19, 15));
        rs2_ = static_cast<RegId> (get_bits(code, 24, 20));

        imm_ = (get_bits(code, 11, 8) << 1) + (get_bits(code, 7, 7) << 11) + (get_bits(code, 30, 25) << 5) + (get_bits((static_cast<int32_t>(code) >> 31), 31, 0) << 12);

        auto funct3 = get_bits(code, 14, 12);

        switch (funct3)
        {
            case 0b000: // BEQ
            {
                inst_tp_ = BEQ;
                break;
            }
            case 0b001: // BNE
            {
                inst_tp_ = BNE;
                break;
            }
            case 0b100: // BLT
            {
                inst_tp_ = BLT;
                break;
            }
            case 0b101: // BGE
            {
                inst_tp_ = BGE;
                break;
            }
            case 0b110: // BLTU
            {
                imm_ = (get_bits(code, 11, 8) << 1) + (get_bits(code, 7, 7) << 11) + (get_bits(code, 30, 25) << 5) + (get_bits(code >> 31, 0, 0) << 12);

                inst_tp_ = BLTU;
                break;
            }
            case 0b111: // BGEU
            {
                imm_ = (get_bits(code, 11, 8) << 1) + (get_bits(code, 7, 7) << 11) + (get_bits(code, 30, 25) << 5) + (get_bits(code >> 31, 0, 0) << 12);

                inst_tp_ = BGEU;
                break;
            }
            default:
            {
                std::cout << "no match with command = " << code << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    default:
        std::cout << "default case:\n";
        std::cout << "no match with opcode = " << unsigned(type) << std::endl;
        exit(EXIT_FAILURE);

        break;
    }


};
