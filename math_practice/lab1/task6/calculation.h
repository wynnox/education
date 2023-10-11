#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <float.h>

enum errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum errors convert_str_to_double (const char *str, double * result);
double rectangle_method(double a, double b, int n, double epsilon, double (*f)(double));
double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);

#endif