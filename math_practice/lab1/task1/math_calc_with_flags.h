#ifndef MATH_CALC_WITH_FLAGS_H_
#define MATH_CALC_WITH_FLAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <string.h>

enum Errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT,
};

enum Errors convert_str_to_int (const char *str, long int * result, int base);

enum Errors multiple_of_a_number (long int number, int** result, int* size_arr_res);
int is_prime (long int number);
enum Errors split_number_to_digits(long int number, char** result, int* size_arr_res);
enum Errors sum_of_numbers (long int number, long long int * result);
enum Errors factorial_of_a_number (long int number, unsigned long long int* result);
enum Errors table_of_degrees(long int*** result, long int number);

#endif