#include "file_processing.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("невалидное число аргументов\n");
        return INVALID_INPUT;
    }

    FILE * input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        printf("не получилось открыть файл\n");
        return ERROR_OPEN_FILE;
    }

    if(strcmp(argv[2], "xor8") == 0)
    {
        if(argc != 3)
        {
            printf("невалидное число аргументов\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        unsigned int result_xor8;
        if (xor8_file(input, &result_xor8) != OK)
        {
            printf("произошла ошибка при вычислении\n");
            if(input != NULL) fclose(input);
            return ERROR_READ_FILE;
        }
        printf("xor8 = %d", result_xor8);
    }
    else if(strcmp(argv[2], "xor32") == 0)
    {
        if(argc != 3)
        {
            printf("невалидное число аргументов\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        unsigned int result_xor32;
        if (xor8_file(input, &result_xor32) != OK)
        {
            printf("произошла ошибка при вычислении\n");
            if(input != NULL) fclose(input);
            return ERROR_READ_FILE;
        }
        printf("xor8 = %d", result_xor32);
    }
    else if (strcmp(argv[2], "mask") == 0)
    {
        if(argc != 4)
        {
            printf("невалидное число аргументов\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        unsigned int mask;
        if(convert_str_to_int(argv[3], &mask, 16) != OK)
        {
            printf("некорректная маска\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        int count_result;
        if(count_xor_mask_file(input, &mask, &count_result) != OK)
        {
            printf("произошла ошибка при вычислении\n");
            if(input != NULL) fclose(input);
            return ERROR_READ_FILE;
        }
        printf("количество чисел в файле, которые соответствуют маске %s(%u): %u\n", argv[3], mask,  count_result);
    }
    else
    {
        printf("такого флага нет в доступных флагах\n");
        if(input != NULL) fclose(input);
        return INVALID_INPUT;
    }

    if(input != NULL) fclose(input);

    return 0;
}