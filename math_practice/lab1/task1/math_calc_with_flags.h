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
    INVALID_INPUT
};

int multiple_of_a_number (long int number, int** result, int* size_arr_res);
int is_prime (long int number);
int split_number_to_digits(long int number, char** result, int* size_arr_res);
int sum_of_numbers (long int number, long long int * result);
int factorial_of_a_number (long int number, unsigned long long int* result);

int count_digits(long int number);

#endif