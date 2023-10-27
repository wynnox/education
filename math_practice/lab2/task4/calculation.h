#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLOW_ERROR
};

typedef struct {
    double x;
    double y;
} Point;

enum errors calculate_polynomial(double * result, double x, int n, ...);
bool is_convex(int count, ...);
double crossProduct(Point first, Point second);

#endif