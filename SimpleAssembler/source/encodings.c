#include "encodings.h"
#include <string.h>

const int register_address(const char* name){
    for (int i = 0; i < 32; i++){
        if (strcmp(Encodings[i].name, name)==0){ return Encodings[i].address;}
        if (strcmp(ABI_names[i].name, name)==0){ return ABI_names[i].address;}
    }
    return -1;
}