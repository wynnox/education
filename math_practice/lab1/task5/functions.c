#include "calculation_of_summ.h"

enum errors convert_str_to_double (const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0' || (*result == 0 && errno == ERANGE))
    {
        return INVALID_INPUT;
    }
    return OK;
}



void taylor_a(double x, double epsilon, double * result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= x/n;
    }
}

void taylor_b(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= (-1.0 * x * x) / (2 * n * (2 * n - 1.0));
    }
}

void taylor_c(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= (9.0 * n * n * x * x) / (9.0 * n * n - 9.0 * n + 2.0);
    }
}

void taylor_d(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = -1.0 * x * x / 2.0;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
    }
}