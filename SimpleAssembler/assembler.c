#include "pch.h"

int main(int argc, char** argv){
    
    // assuming that assembly source file is passed to this assembler as first argument
    // [<simple_assembler> source_file.asm -o ommition_file.*] * ->  format not yet decided
    const char* __assembler_name  = argv[0];
    const char* __assembly_source = argv[1];
    const char* __assembly_ommit  = argv[3];

    return 0;
}