#include "overbullshit.h"

int main()
{
    char buff[256];
    int count;

    printf("\t\tTest 1\n");
    count = oversprintf(buff, "%Ro", 3888);
    printf("format: '%%Ro' 3888\n");
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 2\n");
    count = oversprintf(buff, "over %Ro", 6);
    printf("format: 'over %%Ro' 6\n");
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 3\n");
    count = oversprintf(buff, "over %Roover", 567);
    printf("format: 'over %%Roover' 567\n");
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 4\n");
    count = oversprintf(buff, "over %Roover", 100000000);
    printf("format: 'over %%Roover' 100000000\n");
    printf("str: '%s' count:%d\n\n", buff, count);


    return 0;
}