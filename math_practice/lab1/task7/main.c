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
            FILE * output = fopen(argv[4], "w");
            if(input1 == NULL || input2 == NULL || output == NULL)
            {
                printf("пук\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output != NULL) fclose(output);
                return ERROR_OPEN_FILE;
            }
            char * buff;
            buff = (char *)malloc(101 * sizeof(char));
            if(buff == NULL)
            {
                printf("pupu\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output != NULL) fclose(output);
                return INVALID_MEMORY;
            }

            int len = 0;
            while (!feof(input1) && !feof(input2))
            {
                if(read_input_from_file_into_array(&input2, &buff, &len) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output != NULL) fclose(output);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len > 0) fprintf(output, "%s ", buff);

                if(read_input_from_file_into_array(&input1, &buff, &len) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output != NULL) fclose(output);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len > 0) fprintf(output, "%s ", buff);
            }
            while(!feof(input1))
            {
                if(read_input_from_file_into_array(&input1, &buff, &len) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output != NULL) fclose(output);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len > 0) fprintf(output, "%s ", buff);
            }
            while(!feof(input2))
            {
                if(read_input_from_file_into_array(&input2, &buff, &len) != OK)
                {
                    printf("ту мач лексема, сори, бро");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output != NULL) fclose(output);
                    free(buff);
                    return INVALID_INPUT;
                }
                if(len > 0) fprintf(output, "%s ", buff);
            }
            printf("done\n");
            if(input1 != NULL) fclose(input1);
            if(input2 != NULL) fclose(input2);
            if(output != NULL) fclose(output);
            free(buff);
            break;
        case 'a':

            break;
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            return INVALID_INPUT;
    }
    return 0;
}