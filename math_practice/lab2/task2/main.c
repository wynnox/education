#include "calculation.h"

int main()
{
    double result_pow;
    double base_pow = 20000000;
    int exponent = 200;
    if(fast_pow(base_pow, exponent, &result_pow) == OK)
    {
        printf("%lf^%d = %lf\n", base_pow, exponent, result_pow);
    }
    else
    {
        printf("overflow occurred\n");
    }
    return 0;
}