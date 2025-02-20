cmake_minimum_required(VERSION 3.16.3)

set(PROJ_NAME "Assembly_and_Emulator"   ) # TODO: maybe be creatinve with name for this project.
set(PROJ_LANG LANGUAGES ASM_NASM C CXX  ) # ASM and C to be used primarily and CXX+CUDA for parallel processing
set(PROJ_VERS VERSION  0.00.0           ) # Remember to tweak versions on major.minor.patches
# FIXME: either impliment parallel processing or remove cuda from dependecy, you may need to install nvcc compiler
set(PROJ_DESC DESCRIPTION "Repository for Computer Organization, Winter 2025 semester, assignment at IIITD")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})

if(WIN32)
    set(CMAKE_ASM_NASM_FLAGS "-f win64")  # Force win64 format
endif()

file(GLOB_RECURSE ASSEMBLER_SOURCE
    "${CMAKE_SOURCE_DIR}/SimpleAssembler/*.c"
    # "${CMAKE_SOURCE_DIR}/SimpleAssembler/*.cu"
    # "${CMAKE_SOURCE_DIR}/SimpleAssembler/*.cpp"
    "${CMAKE_SOURCE_DIR}/SimpleAssembler/*.asm"
    "${CMAKE_SOURCE_DIR}/SimpleAssembler/*.h"
)
add_executable(SimpleAssembler ${ASSEMBLER_SOURCE})
target_include_directories(SimpleAssembler PRIVATE "${CMAKE_SOURCE_DIR}/SimpleAssembler/include/")
target_precompile_headers(SimpleAssembler PRIVATE "${CMAKE_SOURCE_DIR}/SimpleAssembler/include/pch.h")
set(${COMPILE_FLAGS} "${COMPILE_FLAGS} -m64")