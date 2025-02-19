#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "pch.h"
#include "commons.h"
#include "encodings.h"
#include "errors.h"

/**
 * @brief structure to obtain and keep track of labels and instructions texts.
 * 
 * This structure holds some essential values and properties related to lines in given assembly files.
 * - `ltype`: enum that shows what type of instruction LABEL/TEXTS is stored on that line.
 * - `lNo`: Line Number at which this instruction is defined at.
 * - `aAd`: Absolute address of label, set to 0 if not a label.
 * - `content`: whatever a line may contain.
 */
typedef struct Line{
    enum lType {
        LABEL = 0b01,   // signifies that this line is a label
        TEXTS = 0b10,   // signifies that this line is a code/text line
    } lType;

    unsigned int lNo;       // Line Number at which this instruction is defined at.
    unsigned int aAd;       // Absolute address of label, set to 0 if not a label.
    const char* content;    // whatever a line may contain.
} Line;

bool isLineLexicallyCorrect(Line line);
bool isLineSyntacticallyCorrect(Line line);

bool is_valid_label(const char* _lab);
int calculate_label_occurence(const char* _lab, Line arr[], int length);
int calculate_label_rAd(const char* _lab, unsigned int aAd, Line arr[], int length);

/**
* @breif Checks the syntax of the assembly code.
* 
* This function checks the syntax of the assembly code by performing lexical and syntactical analysis.
* @param file A pointer to the file containing the assembly code.
* @return A boolean value indicating whether the syntax of the assembly code is correct.
*/
bool syntacticalAnalysis(Line arr[], unsigned int length);

/**
* @breif Checks the lexical correctness of the assembly code.
* 
* This function checks the lexical correctness of the assembly code by performing lexical analysis.
* @param file A pointer to the file containing the assembly code.
* @return A boolean value indicating whether the lexical correctness of the assembly code is correct.
*/
bool lexicalAnalysis(Line arr[], unsigned int length);

#endif