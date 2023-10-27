#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

enum errors read_str(FILE *file, char ** str, int* bufsize)
{
    if(*str == NULL)
    {
        *bufsize = 256;
        *str = (char *)malloc(*bufsize * sizeof(char));
        if(*str == NULL)
        {
            return INVALID_MEMORY;
        }
    }

    int index = 0;
    int c = fgetc(file);

    while (c != EOF && c != '\n') {
        if (index >= (*bufsize) - 1) {
            (*bufsize) *= 2;
            char *for_realloc = (char *)realloc(*str, *bufsize);
            if(for_realloc == NULL)
            {
                free(str);
                return INVALID_MEMORY;
            }
            (*str) = for_realloc;
        }
        (*str)[index++] = c;
        c = fgetc(file);
    }
    (*str)[index] = '\0';
    return OK;
}

enum errors search_in_file(char *filename, char * search_str, int * found)
{
    FILE *input = fopen(filename, "r");
    if(input == NULL)
    {
        printf("Failed to open %s\n", filename);
        return ERROR_OPEN_FILE;
    }
    int buff = 0;
    char * str = NULL;
    while(!feof(input))
    {
        if(read_str(input, &str, &buff) != OK)
        {
            free(str);
            fclose(input);
            return INVALID_MEMORY;
        }
        if (strstr(str, search_str)) {
            printf("Substring found in file %s\n", filename);
            (*found) = 1;
            free(str);
            fclose(input);
            return OK;
        }
    }
    free(str);
    fclose(input);
    return OK;
}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("invalid number of arguments\n");
        return INVALID_INPUT;
    }
    FILE *file_list = fopen(argv[1], "r");
    if (file_list == NULL) {
        printf("Failed to open %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    int bufsize = 0;
    char *filename = NULL;
    int *found = mmap(NULL, sizeof(int), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *found = 0;
    while(!feof(file_list))
    {
        if(read_str(file_list, &filename, &bufsize) == INVALID_MEMORY)
        {
            printf("memory allocation error\n");
            fclose(file_list);
            free(filename);
            return INVALID_MEMORY;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            printf("Failed to fork\n");
            return 1;
        }
        else if(pid == 0)
        {
            enum errors status = search_in_file(filename, argv[2], found);
            if(status == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(file_list);
                free(filename);
                return INVALID_MEMORY;
            }
            exit(0);
        }
    }

    int status;
    while (wait(&status) > 0);


    if(*found == 0)
    {
        printf("The string was not found in any file\n");
    }

    fclose(file_list);
    free(filename);
    munmap(found, sizeof(int));

    return 0;
}