#include "find_substring_in_file.h"

int main()
{
    char file_1[] = "tests/1.txt";
    char file_2[] = "tests/2.txt";
    char substr[] = "hello";
    struct Sub * subs;
    int len = 0;
    if (find_substring_in_file(&subs, substr, &len, 2, file_1, file_2) != OK)
    {
        printf("invalid number of arguments\n");
        return INVALID_INPUT;
    }
    struct Sub * current = subs;
    while(current != NULL)
    {
        if(current->flag_open == 0)
        {
            printf("the file %s did not open\n", current->filename);
        }
        else
        {
            printf("file:%s, №%d: idx:%d\n", current->filename, current->line, current->idx);
        }
        current = current->next;
    }
    current = subs;
    while(current != NULL)
    {
        struct Sub * next = current->next;
        free(current->filename);
        free(current);
        current = next;
    }
    return 0;
}
