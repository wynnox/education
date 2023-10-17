#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

enum errors
{
    OK,
    OVERFLOW_ERROR,
    INVALID_INPUT
};

enum errors fast_pow(double base, int exponent, double *result);
enum errors geometric_mean(double* result, int count, ...);
int check_overflow(double * number);

#endif