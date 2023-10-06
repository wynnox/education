#include "file_operations_with_flag.h"

int main(int argc, char * argv[])
{
    if(argc != 5 && argc != 4)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }
    if( !((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0') ) {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
        case 'r':
            if(argc != 5)
            {
                printf("Ошибка: некорректный ввод\n");
                return INVALID_INPUT;
            }
            FILE * input1 = fopen(argv[2], "r");
            FILE * input2 = fopen(argv[3], "r");
            FILE * output_r = fopen(argv[4], "w");
            if(input1 == NULL || input2 == NULL || output_r == NULL)
            {
                printf("пук\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output_r != NULL) fclose(output_r);
                return ERROR_OPEN_FILE;
            }
            char * buff;
            buff = (char *)malloc(101 * sizeof(char));
            if(buff == NULL)
            {
                printf("pupu\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output_r != NULL) fclose(output_r);
                return INVALID_MEMORY;
            }

            int len_r = 0;
            while (!feof(input1) && !feof(input2))
            {
                if(read_input_from_file_into_array(&input2, &buff, &len_r) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len_r > 0) fprintf(output_r, "%s ", buff);

                if(read_input_from_file_into_array(&input1, &buff, &len_r) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len_r > 0) fprintf(output_r, "%s ", buff);
            }
            while(!feof(input1))
            {
                if(read_input_from_file_into_array(&input1, &buff, &len_r) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len_r > 0) fprintf(output_r, "%s ", buff);
            }
            while(!feof(input2))
            {
                if(read_input_from_file_into_array(&input2, &buff, &len_r) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len_r > 0) fprintf(output_r, "%s ", buff);
            }
            printf("done\n");
            if(input1 != NULL) fclose(input1);
            if(input2 != NULL) fclose(input2);
            if(output_r != NULL) fclose(output_r);
            free(buff);
            break;
        case 'a':
            if(argc != 4)
            {
                printf("Ошибка: некорректный ввод\n");
                return INVALID_INPUT;
            }
            FILE * input = fopen(argv[2], "r");
            FILE * output_a = fopen(argv[3], "w");
            char * buffer;
            short * result;
            buffer = (char *)malloc(101 * sizeof(char));
            result = (short *)malloc(100 * sizeof(short));

            if(buffer == NULL || result == NULL)
            {
                printf("pupu\n");
                if(input != NULL) fclose(input);
                if(output_a != NULL) fclose(output_a);
                free(buffer);
                free(result);
                return INVALID_MEMORY;
            }
            int len = 0;
            int count_token = 0;
            while(!feof(input))
            {
                if(read_input_from_file_into_array(&input, &buffer, &len) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input != NULL) fclose(input);
                    if(output_a != NULL) fclose(output_a);
                    free(result);
                    free(buffer);
                    return INVALID_INPUT;
                }
                count_token++;
                if(len > 0 && count_token % 10 == 0)
                {
                    convert_to_lowercase_and_base4(&buffer, len, &result);
                    for(int i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else if (len > 0 && count_token % 2 == 0)
                {
                    convert_to_lowercase(&buffer, len);
                    fprintf(output_a, "%s ", buffer);
                }
                else if (len > 0 && count_token % 5 == 0)
                {
                    convert_to_ascii_base8(&buffer, len, &result);
                    for(int i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else
                {
                    fprintf(output_a, "%s ", buffer);
                }
            }
            printf("done\n");
            if(input != NULL) fclose(input);
            if(output_a != NULL) fclose(output_a);
            free(result);
            free(buffer);
            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            return INVALID_INPUT;
    }
    return 0;
}