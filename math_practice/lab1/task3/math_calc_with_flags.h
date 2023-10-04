#ifndef MATH_CALC_WITH_FLAGS_H_
#define MATH_CALC_WITH_FLAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum Errors convert_str_to_double (const char *str, double * result);
enum Errors convert_str_to_int (const char *str, long int * result, int base);
enum Errors check_triangle(double epsilon, double side1, double side2, double side3, int* result);
int check_overflow_double(double* num, double epsilon);

void swap(double * a, double * b);
void permutation(double *** result, double* array, int size_array, int* count, int n, double epsilon);
int is_duplicate(double *** result, double* array, int size_array, int count, double epsilon);

#endif