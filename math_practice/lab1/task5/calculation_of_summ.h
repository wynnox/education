#ifndef CALCULATION_OF_SUMM_H_
#define CALCULATION_OF_SUMM_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <errno.h>


enum errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum errors convert_str_to_double (const char *str, double * result);

void taylor_a(double x, double epsilon, double* result);
void taylor_b(double x, double epsilon, double* result);
void taylor_c(double x, double epsilon, double* result);
void taylor_d(double x, double epsilon, double* result);


#endif