#ifndef NUMBER_CONVERSION_H
#define NUMBER_CONVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLOW_ERROR
};

enum errors convert_str_to_ll_int (const char *str, long long int * result, int base);
enum errors check_number_validation(char* number, int base);
enum errors convert_to_base(char ** result, long long int number, int base, char * array_base);

#endif