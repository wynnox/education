#include "overbullshit.h"

int main()
{
    char buff[256];

    printf("\t\tTest 1\n");
    oversprintf(buff, "%Ro", 3888);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 2\n");
    oversprintf(buff, "over %Ro", 6);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 3\n");
    oversprintf(buff, "over %Roover", 567);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 4\n");
    oversprintf(buff, "over %Roover", 100000000);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 5\n");
    oversprintf(buff, "over pupupu %Ro", 5);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 6\n");
    oversprintf(buff, "over %", 100000000);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 7\n");
    oversprintf(buff, "over %Cv", 123, 2);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 8\n");
    oversprintf(buff, "over %Cv", -123, 16);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 9\n");
    oversprintf(buff, "over %CV", 123, 2);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 10\n");
    oversprintf(buff, "over %CV", -123, 16);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 11\n");
    oversprintf(buff, "over %to", "1111011", 2);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 12\n");
    oversprintf(buff, "over %to", "-7b", 16);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 13\n");
    oversprintf(buff, "over %TO", "-7B", 10);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 14\n");
    oversprintf(buff, "%mi", -123);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 15\n");
    oversprintf(buff, "%mu", 123);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 16\n");
    oversprintf(buff, "%md", 0.1);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 17\n");
    oversprintf(buff, "%mf", -1.2);
    printf("str: '%s'\n\n", buff);

    printf("\t\tTest 18\n");
    oversprintf(buff, "%Zr", 10);
    printf("str: '%s'\n\n", buff);

    //--------------------------------------------

    FILE * output = fopen("test.txt", "w");
    if(output == NULL) return -1;

    overfprintf(output, "%Ro\n", 3888);

    overfprintf(output, "over %Ro\n", 6);

    overfprintf(output, "over %Roover\n", 567);

    overfprintf(output, "over %Roover\n", 100000000);

    overfprintf(output, "over %'.2f pupupu %Ro\n", 1234567.89, 5);

    overfprintf(output, "over %\n", 100000000);

    overfprintf(output, "over %Cv\n", 123, 2);

    overfprintf(output, "over %Cv\n", -123, 16);

    overfprintf(output, "over %CV\n", 123, 2);

    overfprintf(output, "over %CV\n", -123, 16);

    overfprintf(output, "over %to\n", "1111011", 2);

    overfprintf(output, "over %to\n", "-7b", 16);

    overfprintf(output, "over %TO\n", "-7B", 10);

    overfprintf(output, "%mi\n", -123);

    overfprintf(output, "%mu\n", 123);

    overfprintf(output, "%md\n", 0.1);

    overfprintf(output, "%mf\n", -1.2);

    overfprintf(output, "%Zr\n", 10);

    fclose(output);

    return 0;
}