#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <float.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum errors
{
    OK,
    INVALID_INPUT,
    OVERFLOW_ERROR
};

enum errors convert_str_to_double (const char *str, double * result);
double power_binary(double base, int exponent);
int is_prime (int number);
double sum(int n);

double limit_e(double epsilon);
double row_e(double epsilon);
double equation_e(double epsilon);

double limit_pi(double epsilon);
double row_pi(double epsilon);
double equation_pi(double epsilon);

double limit_ln(double epsilon);
double row_ln(double epsilon);
double equation_ln(double epsilon);

double limit_sqrt(double epsilon);
double row_sqrt(double epsilon);
double equation_sqrt(double epsilon);

double limit_y(double epsilon);
double row_y(double epsilon);
double equation_y(double epsilon);




#endif