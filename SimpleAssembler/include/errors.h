#ifndef ERRORS_H
#define ERRORS_H

#include "pch.h"

void trace_name_error(unsigned int lNo, const char* content, const char* name, const char* expected);
void trace_type_error(unsigned int lNo, const char* content, const char* type, const char* expected);
void trace_sytx_error(unsigned int lNo, const char* content, const char* message);

#endif