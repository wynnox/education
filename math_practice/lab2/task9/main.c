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
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int is_finite_representation(double number, int base)
{
    int denominator = base;

    // избавляемся от дробной части и переводим в нужную сс
    while (fabs(number - floor(number)) > EPSILON)
    {
        number *= base;
        denominator *= base;
    }

#ifdef DEBUG
    printf("%lf\n", number);
#endif

    int gcd_ = gcd(denominator, base);
    while (gcd_ != 1)
    {
        if (denominator % gcd_ == 0)
        {
            denominator /= gcd_;
        }
        else
        {
            return 0;
        }
        gcd_ = gcd(denominator, base);
    }

    return 1;
}

enum errors check_finite_representation(double **res, int base, int *idx, int count, ...)
{
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

    // Тест 1: числа, которые имеют конечное представление в системе счисления с основанием 2
    if (check_finite_representation(&res, 2, &count ,3, 0.5, 0.25, 0.375) != OK)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
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
    printf("\n");

    // Тест 2: числа, которые не имеют конечного представления в системе счисления с основанием 2
    res = NULL;
    count = 0;
    if (check_finite_representation(&res, 2, &count ,2, 0.3333, 0.6666) != OK)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
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
    printf("\n");


    // Тест 3: числа, которые имеют конечное представление в системе счисления с основанием 3
    res = NULL;
    count = 0;
    if (check_finite_representation(&res, 3, &count ,3, 0.5, 0.25, 0.375) != OK)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
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
    printf("\n");

    // Тест 4: числа, которые не имеют конечного представления в системе счисления с основанием 3
    res = NULL;
    count = 0;
    if (check_finite_representation(&res, 2, &count ,2, 0.3333333333333333, 0.6666666666666666) != OK)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
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
