#ifndef ASSEMBLER_H
#define ASSEMBLER_H


#include "pch.h"
#include "analysis.h"
#include "commons.h"
#include "configs.h"
#include "errors.h"
#include "translator.h"

BYTECODE Instruction_to_ByteCode(Line line);

#ifdef _WIN32
    #include <direct.h>
    #define get_cwd _getcwd
    #define PATH_SEPERATOR "\\"
#else
    #include <unistd.h>
    #define get_cwd getcwd
    #define PATH_SEPERATOR "/"
#endif

#endif