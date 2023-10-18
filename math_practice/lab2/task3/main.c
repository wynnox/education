#include "find_substring_in_file.h"

int main()
{
    char file_1[] = "tests/1.txt";
    char file_2[] = "tests/2.txt";
    char substr[] = "\n";
    if (find_substring_in_file(substr, 2, file_1, file_2) != OK)
    {
        printf("invalid number of arguments\n");
        return INVALID_INPUT;
    }
    return 0;
}