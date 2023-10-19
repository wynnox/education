#ifndef SUM_IN_BASE_H_
#define SUM_IN_BASE_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 100

enum errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT
};

enum errors sum_in_base(char ** result, int base, int count_number, ...);
int check_valid(int base, char ** number);
void reverse(char ** number, int len);
void sum_of_numbers(char ** result, char * number, int base, int * len_res, int len_num);

#endif