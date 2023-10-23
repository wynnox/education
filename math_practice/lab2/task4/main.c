#include "calculation.h"

int main()
{
    double result;
    enum errors err;

    //тест 1
    printf("\ttest 1\n2x^2 + 3x + 4 at x = 1\nexpected result: 9\n");
    err = calculate_polynomial(&result, 1.0, 2, 2.0, 3.0, 4.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 2
    printf("\n\ttest 2\n1x^3 + 2x^2 + 3x + 4 at x = 2\nexpected result: 26\n");
    err = calculate_polynomial(&result, 2.0, 3, 1.0, 2.0, 3.0, 4.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 3
    printf("\n\ttest 3\n1x^4 + 2x^3 + 3x^2 + 4x + 5 at x = 2\nexpected result: 57\n");
    err = calculate_polynomial(&result, 2.0, 4, 1.0, 2.0, 3.0, 4.0, 5.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 4
    printf("\n\ttest 4\n1x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6 at x = 1\nexpected result: 21\n");
    err = calculate_polynomial(&result, 1.0, 5, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 5
    printf("\n\ttest 5\nOverflow check\nexpected result: error\n");
    err = calculate_polynomial(&result, 1e307, 2, 1e307, 1e307, 1e307);
    if(err == OVERFLOW_ERROR)
    {
        printf("\t\t result: Overflow error\n");
    }
    else
    {
        printf("error\n");
    }

    return 0;
}