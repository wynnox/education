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
int check_overflow(double * number);

#endif