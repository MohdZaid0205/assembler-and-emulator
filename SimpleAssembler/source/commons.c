#include "commons.h"

void string_splitter(const char* input, char words[10][10], char delimiters[]) {

    int wordsCount = 0;
    int wordIndex = 0;
    char word[10];
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (strchr(delimiters, input[i]) != NULL) {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                strcpy(words[wordsCount], word);
                wordsCount++;
                wordIndex = 0;
            }
        }
        else {
            word[wordIndex++] = input[i];
        }
    }

    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        strcpy(words[wordsCount], word);
        wordsCount++;
    }

    words[wordsCount][0] = '\0';
}

void intToBinaryString(int num, char* str) {
    str[32] = '\0';

    for (int i = 32 - 1; i >= 0; i--) {
        str[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
}