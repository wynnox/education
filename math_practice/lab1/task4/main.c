#include "file_operations_with_flag.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }

    if( !((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][2] == '\0' || argv[1][3] == '\0')) ) {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    FILE *input = fopen(argv[2], "r");
    if (input == NULL)
    {
        printf("Ошибка: не получилось открыть файл %s\n", argv[2]);
        return ERROR_OPEN_FILE;
    }

    FILE *output = NULL;
    int size_flag = strlen(argv[1]);
    if(size_flag == 3)
    {
        if (argc != 4)
        {
            printf("Ошибка: некорректный ввод");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
        char *n = strchr(argv[1], 'n');
        if(n != NULL)
        {
            output = fopen(argv[3], "w");
            if(output == NULL)
            {
                printf("Ошибка: не получилось открыть файл %s\n", argv[3]);
                if(input != NULL) fclose(input);
                return ERROR_OPEN_FILE;
            }
        }
        else
        {
            printf("Ошибка: некорректный ввод");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }
    }
    else if (size_flag == 2)
    {
        if(argc != 3)
        {
            printf("Ошибка: некорректный ввод");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }


        char * output_filename = (char*)malloc( (strlen(argv[2]) + strlen("/out_") + 1) * sizeof(char) );
        if(output_filename == NULL)
        {
            printf("Ошибка: некорректный ввод\n");
            if(input != NULL) fclose(input);
            return INVALID_INPUT;
        }

        char * end_address = strchr(argv[2], '/');
        if (end_address == NULL)
        {
            strcpy(output_filename, "out_");
            strcat(output_filename, argv[2]);
            output_filename[strlen(argv[2]) + 4] = '\0';
        }
        else
        {
            char * temp_ptr = argv[2];
            size_t _size = strlen(argv[2]);
            size_t shift = _size - strlen(end_address);
            memcpy(output_filename, temp_ptr, shift);
            temp_ptr += shift;
            memcpy(output_filename + shift, "/out_", 5);
            shift += 5;
            memcpy(output_filename + shift, end_address + 1, strlen(end_address) - 1);
            output_filename[_size + 4] = '\0';
        }


        output = fopen(output_filename, "w");
        if(output == NULL)
        {
            printf("Ошибка: не получилось открыть файл %s\n", output_filename);
            if(input != NULL) fclose(input);
            return ERROR_OPEN_FILE;
        }
    }

//    if(output == NULL)
//    {
//        printf("Ошибка: не получилось открыть файл\n");
//        if(input != NULL) fclose(input);
//        return ERROR_OPEN_FILE;
//    }

    switch (argv[1][size_flag - 1])
    {
        case 'd':
            remove_arabic_numerals(input, output);
            printf("Из исходного файла удалены арабские цифры\n");
            break;
        case 'i':
            counter_latin_letter(input, output);
            printf("Количество латинских букв в каждой строке посчитано\n");
            break;
        case 's':
            counter_character(input, output);
            printf("Количество букв в каждой строке посчитано\n");
            break;
        case 'a':
            replacing_numbers(input, output);
            printf("Замена символов произведена\n");
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            if(input != NULL) fclose(input);
            if(output != NULL) fclose(output);
            return INVALID_INPUT;
    }

    if(input != NULL) fclose(input);
    if(output != NULL) fclose(output);

    return 0;
}