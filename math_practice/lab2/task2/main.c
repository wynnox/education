#include "calculation.h"

int main()
{
    double result_pow;
    double base_pow = 20000000;
    int exponent = -1;
    enum errors status = fast_pow(base_pow, exponent, &result_pow);
    if(status == OK)
    {
        printf("%lf^%d = %lf\n", base_pow, exponent, result_pow);
    }
    else if (status == OVERFLOW_ERROR)
    {
        printf("overflow occurred\n");
    }
    else
    {
        printf("incorrect degree");
    }
    return 0;
}