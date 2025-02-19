#ifndef COMMON_H
#define COMMON_H

#include "pch.h"

/**
 * @breif Splits a string into words.
 *
 * This function splits a string into words based on the delimiters provided.
 * @param input The string to be split.
 * @param words The array of words into which the string will be split.
 * @param delimiters The delimiters based on which the string will be split.
 */
void string_splitter(const char* input, char words[10][10], char delimiters[]);

/**
* @breif Converts an integer to a binary string.
 *
 * This function converts an integer to a binary string.
 * @param num The integer to be converted.
 * @return The binary string.
 */
void intToBinaryString(int num, char* str);

#endif