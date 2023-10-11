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


double limit_e(double epsilon)
{
    double n = 1;
    double current = 0, previous = 0;
    do
    {
        previous = current;
        n *= 2;
        current = pow((1.0 + 1.0 / n) , n);
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_pi(double epsilon)
{
    int n = 2;
    double current = 4.0, previous = 0;
    do
    {
        previous = current;
        current *= (4.0 * n * ( n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_ln(double epsilon)
{
    double n = 1;
    double current = 0, previous = 0;
    do
    {
        previous = current;
        n *= 2;
        current = n * (pow(2.0, 1.0 / n) - 1.0);
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double limit_sqrt(double epsilon)
{
    double n = 1;
    double current = -0.5, previous = 0;
    do
    {
        previous = current;
        n ++;
        current = (2.0 * previous - pow(previous, 2.0) + 2.0)/2.0;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double row_e(double epsilon)
{
    double current = 0.0, previous = 0;
    double factorial = 1;
    for(int n = 0; n < 20; ++n)
    {
        factorial *= n;
        if(n == 0) factorial = 1;
        current += 1.0/factorial;
        if((current - previous) < epsilon)
            return current;
        previous = current;
    }
    return current;
}

double row_pi(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;
    do
    {
        previous = current;
        n++;
        current -= 1.0/(2.0 * n - 1.0);
        n++;
        current += 1.0/(2.0 * n - 1.0);
    } while (fabs(previous - current) >= epsilon);
    return current * 4;
}

double row_ln(double epsilon)
{
    int n = 1;
    double current = 1.0, previous = 0;
    do
    {
        previous = current;
        n++;
        current -= 1.0/n;
        n++;
        current += 1.0/n;
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double row_sqrt(double epsilon)
{
    int k = 2;
    double current = pow(2.0, 1.0/4.0), previous = 0;
    do
    {
        previous = current;
        ++k;
        current *= pow(2,1.0/pow(2,k));
    } while (fabs(previous - current) >= epsilon);
    return current;
}

double equation_e(double epsilon)
{
    double x = 3;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = log(x) - 1;
        df = 1.0 / x;
        x = x - f / df;
    }
    return x;
}

double equation_pi(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = cos(x) + 1;
        df = -sin(x);
        x = x - f / df;
    }
    return x;
}

double equation_ln(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }
    return x;
}

double equation_sqrt(double epsilon)
{
    double x = 1;
    double f = 1, df;
    while (fabs(f) > epsilon)
    {
        f = x * x - 2;
        df = 2 * x;
        x = x - f / df;
    }
    return x;
}

double sum(int n)
{
    double sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum += 1.0/i;
    }

    return sum;

}

double limit_y(double epsilon)
{
    double previous = 0;
    double current = 1;
    int n = 1;
    do
    {
        previous = current;
        n *= 2;
        current = sum(n) - log(n);

    } while (fabs(previous - current) >= epsilon);

    return current;
}

double row_y(double epsilon)
{
    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;
    do
    {
        previous = current;
        k++;
        l = sqrt(k);
        if (fmod(l,1.0) == 0)
        {
            k++;
            l = (int)pow(k, 1.0/2.0);
        }
        current += 1.0/pow((int)l,2.0) - 1.0/k;


    } while (fabs(previous - current) >= epsilon);

    return (current - pow(M_PI,2) / 6);
}

double equation_y(double epsilon)
{
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;
    double product = 0.5;
    do
    {
        previous = current;
        do
        {
            p++;
        } while (is_prime(p));
        product *= (p - 1.0)/p;
        current = log(p) * product;


    } while (fabs(previous - current) >= epsilon);
    return (-log(current));
}

int is_prime (int number)
{
    if(number < 0) number *= -1;

    if (number == 0 || number == 1 || number == 2)
        return 0;

    if(number % 2 == 0) return 1;

    for (int i = 3; i <= floor(sqrt(number)); i+=2)
    {
        if (number % i == 0)
            return 1;
    }
    return 0;
}