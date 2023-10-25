#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;
    pid=fork();
    printf("%d\n", pid);
    return 0;
}