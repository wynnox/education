#include "calculation.h"

int check_overflow(double * number)
{
    if(isnan(*number) || isinf(*number))
    {
        return 1;
    }
    return 0;
}

enum errors fast_pow(double base, int exponent, double *result)
{
    enum errors status;
    if(exponent == 0)
    {
        *result = 1.0;
        return OK;
    }
    if(exponent % 2 == 0)
    {
        status = fast_pow(base, exponent / 2, result);
        if(check_overflow(result))
        {
            return OVERFLOW_ERROR;
        }
        *result *= *result;
    }
    else
    {
        status = fast_pow(base, exponent - 1, result);
        if(check_overflow(result))
        {
            return OVERFLOW_ERROR;
        }
        *result *= base;
    }
    return status;
}

