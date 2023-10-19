#include "sum_in_base.h"

int main()
{
    char * result;
    enum errors err;

    //тест 1
    printf("\ttest 1\n1 + 99 (notation 10)\nexpected result: 100\n");
    err = sum_in_base(&result, 10, 2, "1", "99");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 2
    printf("\n\ttest 2\n123 + 456 (notation 10)\nexpected result: 579\n");
    err = sum_in_base(&result, 10, 2, "123", "456");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 3
    printf("\n\ttest 3\nA + B + C (notation 16)\nexpected result: 21\n");
    err = sum_in_base(&result, 16, 3, "A", "B", "C");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 4
    printf("\n\ttest 4\n123 + 456 (notation 37)\nexpected result: error\n");
    err = sum_in_base(&result, 37, 2, "123", "456");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 5
    printf("\n\ttest 5\n0 + 23456789 (notation 10)\nexpected result: 23456789\n");
    err = sum_in_base(&result, 10, 2, "0", "23456789");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 6
    printf("\n\ttest 6\n123456765432 + 0 (notation 10)\nexpected result: 123456765432\n");
    err = sum_in_base(&result, 10, 2, "123456765432", "0");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 7
    printf("\n\ttest 7\n0 + 0 (notation 10)\nexpected result: 0\n");
    err = sum_in_base(&result, 10, 2, "0", "0");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }
    free(result);

    //тест 8
    printf("\n\ttest 8\ncount_number = 0 (notation 10)\nexpected result: error\n");
    err = sum_in_base(&result, 10, 0);
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 9
    printf("\n\ttest 9\n'' + '' (notation 10)\nexpected result: error\n");
    err = sum_in_base(&result, 10, 2, "", "");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    //free(result);

    //тест 10
    printf("\n\ttest 10\n99999999999999999999 + 99999999999999999999 (notation 10)\nexpected result: 199999999999999999998\n");
    err = sum_in_base(&result, 10, 2, "99999999999999999999", "99999999999999999999");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //тест 11
    printf("\n\ttest 11\n1101 + 1011 (notation 2)\nexpected result: 11000\n");
    err = sum_in_base(&result, 2, 2, "1101", "1011");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //тест 12
    printf("\n\ttest 12\n-123 + -456 (notation 10)\nexpected result: error\n");
    err = sum_in_base(&result, 10, 2, "-123", "-456");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }

    //тест 13
    printf("\n\ttest 13\n000123 + 00456 (notation 10)\nexpected result: 579\n");
    err = sum_in_base(&result, 10, 2, "000123", "00456");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //тест 14
    printf("\n\ttest 14\n123 + 456 (notation 8)\nexpected result: 601\n");
    err = sum_in_base(&result, 8, 2, "123", "456");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //test 15
    printf("\n\ttest 15\nABCDEF + FEDCBA (notation 16)\nexpected result: 1C9C38\n");
    err = sum_in_base(&result, 16, 2, "ABCDEF", "FEDCBA");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //test 16
    printf("\n\ttest 16\nA + B + C + D (notation 16)\nexpected result: 2A\n");
    err = sum_in_base(&result, 16, 4, "A", "B", "C", "D");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //test 17
    printf("\n\ttest 17\nZ + A (notation 26)\nexpected result: 11\n");
    err = sum_in_base(&result, 26, 2, "Z", "A");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //test 18
    printf("\n\ttest 18\nV + 1 (notation 32)\nexpected result: 12\n");
    err = sum_in_base(&result, 32, 2, "V", "1");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    //test 19
    printf("\n\ttest 19\nZ + Y + X + W (notation 26)\nexpected result: 3S\n");
    err = sum_in_base(&result, 26, 4, "Z", "Y", "X", "W");
    if(err == OK)
    {
        printf("\t\t result: %s\n", result);
    } else {
        printf("error\n");
    }
    free(result);

    return 0;
}