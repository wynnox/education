#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

enum errors
{
    OK,
    INVALID_MEMORY,
    INVALID_INPUT
};

int gcd(int a, int b)
{
    while (a > 0 && b > 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    if (a == 0)
    {
        return b;
    }
    return a;
}

int is_finite_representation(double number, int base)
{
    int numerator, denominator = 1;

    while (fabs(number - floor(number)) > EPSILON)
    {
        number *= 10;
        denominator *= 10;
    }

    numerator = (int)number;
#ifdef DEBUG
    printf("%d %d\n", numerator, denominator);
#endif

//    numerator = (int)number;
    int gcd_ = gcd(numerator, denominator);
    if(gcd_ != 1)
    {
        denominator /= gcd_;
    }

    int i = 2;
    if(denominator % i == 0 && base % i != 0)
    {
        return 0;
    }
    while(denominator % i == 0)
        denominator /= i;

    for(int i = 3; i <= sqrt(denominator); i+=2)
    {
        if(denominator % i == 0 && base % i != 0)
        {
            return 0;
        }
        while(denominator % i == 0)
            denominator /= i;
    }


    return 1;
}

enum errors check_finite_representation(double **res, int base, int *idx, int count, ...)
{
    if (base < 2)
    {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, count);

    *res = (double *)malloc(sizeof(double) * count);
    if (*res == NULL)
    {
        return INVALID_MEMORY;
    }

    *idx = 0;

    for (int i = 0; i < count; ++i)
    {
        double number = va_arg(args, double);

        if (number > 1 - EPSILON || number < EPSILON)
        {
            printf("fraction %lf is invalid\n", number);
            continue;
        }

        if (is_finite_representation(number, base) == 1)
        {
            (*res)[(*idx)++] = number;
        }
    }

    if (*idx == 0)
    {
        free(*res);
        *res = NULL;
    }

    va_end(args);
    return OK;
}

int main()
{
    double *res = NULL;
    int count = 0;

    enum errors err = check_finite_representation(&res, 25, &count, 3, 0.04, 0.0004, 0.37);
    if (err == INVALID_MEMORY)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
    }
    else if(err == INVALID_INPUT)
    {
        printf("invalid base\n");
        return INVALID_INPUT;
    }

    if (count == 0)
    {
        printf("No numbers have finite representation\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("%lf has finite representation\n", res[i]);
        }

        free(res);
    }

    return 0;
}
