#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();
    printf("Hi\n");
    fork();
    printf("Hi\n");
    return 0;
}