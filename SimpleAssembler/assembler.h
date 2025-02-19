#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "pch.h"
#include "analysis.h"
#include "commons.h"
#include "configs.h"
#include "errors.h"
#include "translator.h"

#ifdef _WIN32
    #include <direct.h>
    #define get_cwd _getcwd
#else
    #include <unistd.h>
    #define get_cwd getcwd
#endif

#endif