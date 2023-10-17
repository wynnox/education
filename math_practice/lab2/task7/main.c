#include "calculation.h"

int main()
{
    double result;
    enum dichotomy status = method_dichotomy(&result, M_PI / 2, 3 * M_PI / 2, func5, 1e-20);
    if(status == OK)
    {
        printf("root is %lf\n", result);
    }
    else if (status == NO_ROOTS)
    {
        printf("No roots in the interval\n");
    }
    else
    {
        printf("incorrect epsilon\n");
    }

    return 0;
}