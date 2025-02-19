#include "assembler.h"

int main(int argc, char** argv){
    
    // assuming that assembly source file is passed to this assembler as first argument
    // assuming format for input argparse to be:
    //      SimpleAssembler -file source.asm -out source.exe
    const char* argparse_executable = argv[0];

    char _curr_working_directory[1024]; // for file read/write
    int _cwd_status = get_cwd(_curr_working_directory, 1024);
    
    return 0;
}