#include "overbullshit.h"

int main()
{
    char buff[256];
    int count;

    printf("\t\tTest 1\n");
    count = oversprintf(buff, "%Ro", 3888);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 2\n");
    count = oversprintf(buff, "over %Ro", 6);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 3\n");
    count = oversprintf(buff, "over %Roover", 567);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 4\n");
    count = oversprintf(buff, "over %Roover", 100000000);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 5\n");
    count = oversprintf(buff, "over %'.2f pupupu %Ro", 1234567.89, 5);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 6\n");
    count = oversprintf(buff, "over %", 100000000);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 7\n");
    count = oversprintf(buff, "over %Cv", 123, 2);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 8\n");
    count = oversprintf(buff, "over %Cv", -123, 16);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 9\n");
    count = oversprintf(buff, "over %CV", 123, 2);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 10\n");
    count = oversprintf(buff, "over %CV", -123, 16);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 11\n");
    count = oversprintf(buff, "over %to", "1111011", 2);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 12\n");
    count = oversprintf(buff, "over %to", "-7b", 16);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 13\n");
    count = oversprintf(buff, "over %TO", "-7B", -1);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 14\n");
    int k;
    count = oversprintf(buff, "over %n over", &k);
    printf("format: 'over %%n over', '&k'\n");
    printf("str: '%s' count:%d int k = %d\n\n", buff, count, k);

    printf("\t\tTest 15\n");
    count = oversprintf(buff, "%mi", -123);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 16\n");
    count = oversprintf(buff, "%mu", 123);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 17\n");
    count = oversprintf(buff, "%md", 0.1);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 18\n");
    count = oversprintf(buff, "%mf", -1.2);
    printf("str: '%s' count:%d\n\n", buff, count);

    printf("\t\tTest 19\n");

    return 0;
}