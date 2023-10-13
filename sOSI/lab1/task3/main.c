#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("инвалидный импут\n");
        return 1;
    }
    FILE * input;
    FILE * output;

    input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("ошибка при открытии файла\n");
        return 1;
    }
    output = fopen(argv[2], "w");
    if(output == NULL)
    {
        printf("ошибка при открытии файла\n");
        if(input != NULL) fclose(input);
        return 1;
    }

    char c = fgetc(input);
    while (!feof(input))
    {
        if(fputc(c, output) == EOF)
        {
            printf("произошла ошибка при записи байта\n");
            if(input != NULL) fclose(input);
            if(output != NULL) fclose(output);
            return 1;
        }
        c = fgetc(input);
    }
    printf("файл %s скопирован в файл %s\n", argv[1], argv[2]);
    if(input != NULL) fclose(input);
    if(output != NULL) fclose(output);
    return 0;
}