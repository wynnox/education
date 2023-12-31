#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
};

//Функция для вычисления значения полинома в точке argument с заданными коэффициентами coefs и степенью power
double evaluate_polynomial(double argument, double *coefs, int max_power)
{
    double result = 0;
    double current_power = 1;
    for (int i = 0; i <= max_power; i++)
    {
        result += current_power * coefs[i];
        current_power *= argument;
    }
    return result;
}

enum errors calculate_polynomial(double a, double **coefficients, int degree, ...)
{
    if (degree < 0) return INVALID_INPUT;

    (*coefficients) = (double *)malloc((degree + 1) * sizeof(double));
    if ((*coefficients) == NULL)
    {
        return INVALID_MEMORY;
    }

    int n = degree;
    double *start_coefficients = (double *)malloc(sizeof(double) * (degree + 1));
    if (start_coefficients == NULL)
    {
        free(*coefficients);
        return INVALID_MEMORY;
    }

    va_list args;
    va_start(args, degree);
    for (int i = 0; i <= degree; i++)
    {
        double coefficient = va_arg(args, double);
        start_coefficients[i] = coefficient;
    }
    va_end(args);

    double multiply = 1.0;
    int curr_power = degree;
    for (int i = 0; i <= n; i++)
    {
        (*coefficients)[i] = evaluate_polynomial(a, start_coefficients, curr_power);
        if (i > 1)
        {
            multiply *= i;
            (*coefficients)[i] /= multiply;
        }

        curr_power--;
        for(int j = 0; j <= curr_power; ++j)
        {
            double b = start_coefficients[j + 1];
            start_coefficients[j] = b * (j + 1);
        }
    }

    free(start_coefficients);
    return OK;
}

int main()
{
    double *result;
    enum errors err;

    err = calculate_polynomial(3.0, &result, 4, -2.0, 1.0, -3.0, 0.0, 1.0);
    if (err == OK)
    {
        for (int i = 0; i <= 4; ++i)
        {
            printf("%lf ", result[i]);
        }
        printf("\n");
    }
    else
    {
        printf("error\n");
    }
    free(result);
    return 0;
}
