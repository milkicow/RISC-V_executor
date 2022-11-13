# RISC-V_executor
My implementation of RISC-V interpreter that can execute commands from elf file

## Requirements
  1. RISC-V compiler for creating elf-file
  2. g++
  3. cmake
  
 ## Creating ELF
  You need to download risc toolchain from this git repository and config fot RISC32I:
```
https://github.com/riscv-collab/riscv-gnu-toolchain
``` 

After many hours of clonning you need to compile program:
```
riscv32-unknown-elf-gcc -S program_name.c -o program_name.s
riscv32-unknown-elf-as program_name.s -o program_name.o
riscv32-unknown-elf-ld program_name.o -o program_name.out
riscv32-unknown-elf-objdump -S program_name.out > program_name.dump
```
You must create dump file because this interpeter parse it: project was developed on arm - no libelf for parse (in future plans)

## Compiling RISC-V_executor

Create dir "build" and do "cmake" and "make" in it 
```
mkdir build
cmake ..
make all
```
## Run the program

You can find exe bin file in build/bin
(Also there is logfile with dump of instructions and regs)

You must put dump_file as argument

```
cd build/bin
./risc file_name.dump
```

## Examples 
You can see some program examples in eponymous directory
