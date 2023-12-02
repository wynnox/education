#include "number_base_detection.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if(input == NULL || output == NULL)
    {
        printf("Ошибка: не получилось открыть файл\n");
        if(input != NULL) fclose(input);
        if(output != NULL) fclose(output);
        return ERROR_OPEN_FILE;
    }

    int capacity = 2;
    char * buffer = (char *)malloc(capacity * sizeof(char));
    if(buffer == NULL)
    {
        printf("Ошибка: ошибка при выделении памяти");
        return INVALID_MEMORY;
    }

    int len = 0;
    int min_base = 2;

    while (!feof(input))
    {
        enum errors err = read_input_from_file_into_array(&input, &buffer, &len, &min_base, &capacity);
        if(err == INVALID_INPUT)
        {
            if(input != NULL) fclose(input);
            if(output != NULL) fclose(output);
            free(buffer);
            printf("некорректный ввод");
            return INVALID_INPUT;
        }
        else if(err == INVALID_MEMORY)
        {
            free(buffer);
            printf("INVALID_MEMORY\n");
            fclose(input);
            fclose(output);
            return INVALID_MEMORY;
        }
        if(len > 0)
        {
            long long int number_base10 = 0;
            if (convert_str_to_ll_int(buffer, &number_base10, min_base) != OK)
            {
                if (input != NULL) fclose(input);
                if (output != NULL) fclose(output);
                free(buffer);
                return INVALID_INPUT;
            }
            fprintf(output, "входное число: %s\n", buffer);
            fprintf(output, "минимальное основание: %d\n", min_base);
            fprintf(output, "число в 10 сс: %lld\n", number_base10);
            fprintf(output, "\n");
        }
    }

    printf("Запись в файл сделана\n");

    if (input != NULL) fclose(input);
    if (output != NULL) fclose(output);
    free(buffer);

    return 0;
}

