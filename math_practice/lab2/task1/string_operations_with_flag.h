#ifndef STRING_OPERATIONS_WITH_FLAG_H_
#define STRING_OPERATIONS_WITH_FLAG_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

enum errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT
};

int string_len(const char * str);
enum errors string_reverse(const char * str, char ** result);
enum errors convert_odd_chars_to_upper(const char * str, char ** result);
enum errors reorder_string(const char * str, char ** result);
enum errors convert_str_to_int (const char *str, unsigned int * result, int base);
enum errors concatenate_randomly(char ** strs, int count_str, char ** result, unsigned int seed);
void concat_string(char * str, char ** result, int * len);


#endif