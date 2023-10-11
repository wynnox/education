#include "calculation.h"

enum errors convert_str_to_double (const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (errno == ERANGE && (*result == HUGE_VAL || *result == -HUGE_VAL))
    {
        return INVALID_INPUT;
    } else if (errno == ERANGE && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

double integral_a(double x)
{
    return log(1 + x) / x;
}

double integral_b(double x)
{
    return exp(-x*x/2);
}

double integral_c(double x)
{
    return log(1/(1 - x));
}

double integral_d(double x)
{
    return pow(x, x);
}

double rectangle_method(double a, double b, int n, double epsilon, double (*f)(double))
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (double i = epsilon; i < n - epsilon; i++) {
        double x = a + h * i;
        sum += f(x);
    }
    return h * sum;
}