#include "errors.h"

const char* ERROR = "\x1b[48;2;255;125;125m[ ERROR ]\x1b[0m : ";
const char* WARNING = "\x1b[48;2;255;255;125m[ ERROR ]\x1b[0m : ";

void trace_name_error(unsigned int lNo, const char* content, const char* name, const char* expected){
    printf("%s\x1b[38;2;255;125;125mname error at line no %d\x1b[0m\n", ERROR, lNo);
    printf("\t\tcontent  : %s\n", content);
    printf("\t\tproblems : \x1b[38;2;255;255;125m[%s] is not a valid name for %s\x1b[0m\n", name, expected);
}

void trace_type_error(unsigned int lNo, const char* content, const char* type, const char* expected){
    printf("%s\x1b[38;2;255;125;125mtype error at line no %d\x1b[0m\n", ERROR, lNo);
    printf("\t\tcontent  : %s\n", content);
    printf("\t\tproblems : \x1b[38;2;255;255;125m[%s] is not proper type, expected:%s\x1b[0m\n", type, expected);
    #define RAISED_TYPE_ERROR
}

void trace_sytx_error(unsigned int lNo, const char* content, const char* message){
    printf("%s\x1b[38;2;255;125;125msyntax error at line no %d\x1b[0m\n", ERROR, lNo);
    printf("\t\tcontent  : %s\n", content);
    printf("\t\tproblems : \x1b[38;2;255;255;125m%s\x1b[0m\n", message);
    #define RAISED_SYTX_ERROR
}

void trace_cstm_error(const char* about, const char* message){
    printf("%s\x1b[38;2;255;125;125m %s\x1b[0m\n", ERROR, about);
    printf("\t\tproblems : \x1b[38;2;255;255;125m%s\x1b[0m\n", message);
    #define RAISED_CSTM_ERROR
}
