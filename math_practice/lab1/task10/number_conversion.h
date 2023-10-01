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

/*
 * исправить комменты по пути
 * потестить первые вхождения
 * просто много тестить
 */

enum errors convert_str_to_ll_int (const char *str, long long int * result, int base);
enum errors check_number_validation(char* number, int base);
//void converting_number_to_array(long long int number, char* array);

#endif