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
            fclose(input);
            return INVALID_INPUT;
        }
        if(feof(input) == 0)
        {
            printf("пустой файл\n");
            fclose(input);
            return ERROR_READ_FILE;
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
            fclose(input);
            return INVALID_INPUT;
        }
        if(feof(input) == 0)
        {
            printf("пустой файл\n");
            fclose(input);
            return ERROR_READ_FILE;
        }
        size_t size_group = 4;
        unsigned char* group = (unsigned char *)malloc(sizeof(unsigned char) * size_group);
        if(group == NULL)
        {
            fclose(input);
            return INVALID_MEMORY;
        }
        if (xor32_file(input, &group, size_group) != OK)
        {
            printf("произошла ошибка при вычислении\n");
            if(input != NULL) fclose(input);
            free(group);
            return ERROR_READ_FILE;
        }
        printf("xor8 = ");
        for(size_t i = 0; i < size_group; ++i)
        {
            printf("%u ", group[i]);
        }
        printf("\n");
        free(group);
    }
    else if (strcmp(argv[2], "mask") == 0)
    {
        if(argc != 4)
        {
            printf("невалидное число аргументов\n");
            fclose(input);
            return INVALID_INPUT;
        }
        if(feof(input) == 0)
        {
            printf("пустой файл\n");
            fclose(input);
            return ERROR_READ_FILE;
        }
        if(check_mask_validation(&argv[3]) != OK)
        {
            printf("невалидная маска\n");
            fclose(input);
            return INVALID_INPUT;
        }
        int count_result;
        if(count_xor_mask_file(input, &argv[3], &count_result) != OK)
        {
            printf("произошла ошибка при вычислении\n");
            if(input != NULL) fclose(input);
            return ERROR_READ_FILE;
        }
        printf("количество групп в файле, которые соответствуют маске %s: %u\n", argv[3],  count_result);
    }
    else
    {
        printf("такого флага нет в доступных флагах\n");
        fclose(input);
        return INVALID_INPUT;
    }

    if(input != NULL) fclose(input);

    return 0;
}