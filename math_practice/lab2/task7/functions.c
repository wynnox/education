#include "calculation.h"

enum dichotomy method_dichotomy(double * result, double left, double right, double (*f)(double), double epsilon)
{
    if(f(left) * f(right) > 0)
    {
        return NO_ROOTS;
    }
    if(epsilon <= 0)
    {
        return INVALID_INPUT;
    }
    *result = (left + right) / 2;
    while (fabs(f(*result)) >= epsilon)
    {
        if(f(*result) * f(left) < 0)
        {
            right = *result;
        }
        else
        {
            left = *result;
        }
        *result = (left + right) / 2;
    }
    return OK;
}

double func1(double x)
{
    return x - 2;
}

double func2(double x)
{
    return x * x - 3 * x + 2;
}

double func3(double x)
{
    return x * x * x - 6 * x * x + 9 * x - 4;
}

double func4(double x)
{
    return x * x * x * x - 10 * x * x * x + 35 * x * x - 50 * x + 24;
}

double func5(double x)
{
    return sin(x) + 1;
}

double func6(double x)
{
    return x * x;
}