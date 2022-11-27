cmake_minimum_required(VERSION 3.2) 

project(RISC_ELF_EXECUTOR LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE ${PROJECT_SOURCE_DIR}/src/Core.cpp
           ${PROJECT_SOURCE_DIR}/src/Instruction.cpp
           ${PROJECT_SOURCE_DIR}/src/Memory.cpp
           ${PROJECT_SOURCE_DIR}/src/Execute.cpp
           ${PROJECT_SOURCE_DIR}/main.cpp         )
        
add_executable(risc ${SOURCE})
target_include_directories(risc 
                            PRIVATE include)

install(TARGETS risc
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT risc)
