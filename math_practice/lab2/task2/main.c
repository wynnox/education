#include "calculation.h"

int main()
{
    double result_geometric_mean;
    enum errors status_geometric_mean = geometric_mean(&result_geometric_mean, 1, 4., 3., 2., 1.);
    if(status_geometric_mean == OK)
    {
        printf("%lf\n", result_geometric_mean);
    }
    else if (status_geometric_mean == INVALID_INPUT)
    {
        printf("incorrect number of arguments");
    }
    else
    {
        printf("overflow occurred\n");
    }



    double result_pow;
    double base_pow = 4;
    int exponent = -2;
    enum errors status_pow = fast_pow(base_pow, exponent, &result_pow);
    if(status_pow == OK)
    {
        printf("%lf^%d = %lf\n", base_pow, exponent, result_pow);
    }
    else
    {
        printf("overflow occurred\n");
    }
    return 0;
}