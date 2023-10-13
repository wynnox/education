#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Некорректный ввод\n");
        return 1;
    }

    // создание файла с последовательностью байт
    FILE * input;
    input = fopen(argv[1], "wb");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    size_t bufferSize = 11;
    unsigned char* buffer = (unsigned char*) malloc(bufferSize * sizeof(unsigned char));
    if(buffer == NULL)
    {
        printf("ошибка при выделении памяти\n");
        if(input != NULL) fclose(input);
        return 1;
    }

    buffer[0] = 3;
    buffer[1] = 1;
    buffer[2] = 4;
    buffer[3] = 1;
    buffer[4] = 5;
    buffer[5] = 9;
    buffer[6] = 2;
    buffer[7] = 6;
    buffer[8] = 5;
    buffer[9] = 3;
    buffer[10] = 5;

    if(fwrite(buffer, sizeof(unsigned char), bufferSize, input) != bufferSize)
    {
        printf("ошибка при записи в файл\n");
        if(input != NULL) fclose(input);
        free(buffer);
        return 1;
    }

    // закрытие файла и побайтовое чтение с выводом полей структуры
    if(input != NULL) fclose(input);

    input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        free(buffer);
        return 1;
    }

    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), sizeof(byte), input))
    {
        printf("%u\n", byte);
        printf("_fileno: %d\n _flags: %d\n _flags2: %d\n _mode: %d\n _shortbuf: %s\n _unused2: %s\n _vtable_offset: %u\n",
               input->_fileno, input->_flags, input->_flags2, input->_mode, input->_shortbuf, input->_unused2, input->_vtable_offset);
    }

    if(ferror(input))
    {
        printf("ошибка при чтении из файла\n");
        if(input != NULL) fclose(input);
        free(buffer);
        return 2;
    }

    if(input != NULL) fclose(input);

    //открытие файла, перемещение указателя и считывание 4 байта из файла в буфер
    input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        printf("Ошибка при открытии файла\n");
        free(buffer);
        return 1;
    }

    size_t bufSize = 4;
    unsigned char* buf = (unsigned char *)malloc(sizeof(unsigned char) * bufSize);
    if (buf == NULL)
    {
        printf("ошибка при работе с памятью\n");
        if(input != NULL) fclose(input);
        free(buffer);
        return 1;
    }
    fseek(input, 3, SEEK_SET);
    if(fread(buf, sizeof(unsigned char), bufSize, input) != bufSize)
    {
        printf("ошибка при считывании байтов из файла\n");
        if(input != NULL) fclose(input);
        free(buffer);
        free(buf);
        return 1;
    }

    for (size_t i = 0; i < bufSize; ++i)
    {
        printf("%u", buf[i]);
    }
    printf("\n");

    if(input != NULL) fclose(input);
    free(buf);
    free(buffer);
    return 0;
}