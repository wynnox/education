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

enum errors convert_str_to_double (const char *str, double * result);
enum errors convert_str_to_int (const char *str, long int * result, int base);
enum errors check_triangle(double epsilon, double side1, double side2, double side3, int* result);
int check_overflow_double(double* num1, double* num2, double epsilon);

void swap(double * a, double * b);
int check_duplicate(double*** result, int size_result, int *count_array, double* array, double epsilon);
enum errors generation_permutation(double*** result, int size_result, int left, int right, int* count, double* array, double epsilon);

#endif