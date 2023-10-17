#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdio.h>
#include <math.h>

enum dichotomy
{
    OK,
    NO_ROOTS,
    OVERFLOW_ERROR,
    INVALID_INPUT
};

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum dichotomy method_dichotomy(double * result, double left, double right, double (*f)(double), double epsilon);
double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);
double func5(double x);
double func6(double x);

#endif