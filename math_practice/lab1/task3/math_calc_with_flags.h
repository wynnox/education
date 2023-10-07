#ifndef MATH_CALC_WITH_FLAGS_H_
#define MATH_CALC_WITH_FLAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLOW_ERROR
};

enum errors convert_str_to_double (const char *str, long double * result);
enum errors convert_str_to_int (const char *str, long int * result, int base);
enum errors check_triangle(long double epsilon, long double side1, long double side2, long double side3, int* result);
int check_overflow_double(long double* num1, long double* num2, long double epsilon);

void swap(long double * a, long double * b);
int check_duplicate(long double*** result, int size_result, int *count_array, long double* array, long double epsilon);
enum errors generation_permutation(long double*** result, int size_result, int left, int right, int* count, long double* array, long double epsilon);

#endif