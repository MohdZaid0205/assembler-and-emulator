#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "pch.h"

typedef struct Line{
    enum lType {
        LABEL = 0b01,
        TEXTS = 0b10,
    } lType;

    unsigned int lNo;
    const char* content;
} Line;

bool isLineLexicallyCorrect(Line line);
bool isLineSyntacticallyCorrect(Line line);

/**
* @breif Checks the syntax of the assembly code.
* 
* This function checks the syntax of the assembly code by performing lexical and syntactical analysis.
* @param file A pointer to the file containing the assembly code.
* @return A boolean value indicating whether the syntax of the assembly code is correct.
*/
bool syntacticalAnalysis(FILE* file);

/**
* @breif Checks the lexical correctness of the assembly code.
* 
* This function checks the lexical correctness of the assembly code by performing lexical analysis.
* @param file A pointer to the file containing the assembly code.
* @return A boolean value indicating whether the lexical correctness of the assembly code is correct.
*/
bool lexicalAnalysis(FILE* file);

#endif