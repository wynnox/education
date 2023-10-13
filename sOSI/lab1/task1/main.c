#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Некорректный ввод\n");
        return 1;
    }

    FILE * input;
    input = fopen(argv[1], "w");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        return 1;
    }
    if(fwrite("31415926535", sizeof(char), 11, input) != 11)
    {
        printf("ошибка при записи в файл\n");
        return 1;
    }

    fclose(input);

    input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    char c = fgetc(input);
    while(c != EOF)
    {
        printf("\n%c\n _fileno: %d\n _flags: %d\n _flags2: %d\n _mode: %d\n _shortbuf: %s\n _unused2: %s\n _vtable_offset: %u\n",
               c, input->_fileno, input->_flags, input->_flags2, input->_mode, input->_shortbuf, input->_unused2, input->_vtable_offset);
        c = fgetc(input);
    }
    fclose(input);

    input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    char buf[5];
    fseek(input, 3, SEEK_SET);
    if(fread(&buf, sizeof(char), 4, input) != 4)
    {
        printf("ошибка при считывании байтов из файла\n");
        return 1;
    }
    printf("%s", buf);
    fclose(input);
    return 0;
}