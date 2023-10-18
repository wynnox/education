#ifndef FIND_SUBSTRING_IN_FILE_H_
#define FIND_SUBSTRING_IN_FILE_H_

#include <stdarg.h>
#include <stdio.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

enum errors find_substring_in_file(char * str, int count_file, ...);
int string_len(const char * str);

#endif