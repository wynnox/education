#include "number_conversion.h"

int main()
{
    int base;
    if(!scanf("%d", &base) || base > 36 || base < 2)
    {
        printf("Ошибка: некорректное основание системы счисления\n");
        return INVALID_INPUT;
    }

    char* end_of_input = "Stop";
    char * array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char * input_number_array = NULL;

    input_number_array = malloc(sizeof(char) * 101);
    if(input_number_array == NULL)
    {
        printf("Ошибка: ошибка работы с памятью\n");
        return INVALID_MEMORY;
    }

    long long int result_number = 0;
    long long int input_number = 0;
    int flag_stop = 0;
    while(scanf("%100s", input_number_array))
    {
        if(strcmp(input_number_array, end_of_input) == 0)
        {
            if(flag_stop)
            {
                char * result_number_array = NULL;

                if(convert_to_base(&result_number_array, result_number, base, array_base) != OK)
                {
                    printf("Ошибка: я хз как на этом этапе может вылезти ошибка, наверн с памятью что-то\n");
                    if(input_number_array != NULL) free(input_number_array);
                    if(result_number_array != NULL) free(result_number_array);
                    return INVALID_MEMORY;
                }
                printf("%d: %s\n", base, result_number_array);
                for(int i = 3; i < 37; i*=3)
                {
                    if(convert_to_base(&result_number_array, result_number, i, array_base) != OK)
                    {
                        printf("Ошибка: я хз как на этом этапе может вылезти ошибка, наверн с памятью что-то\n");
                        if(input_number_array != NULL) free(input_number_array);
                        if(result_number_array != NULL) free(result_number_array);
                        return INVALID_MEMORY;
                    }
                    printf("%d: %s\n", i, result_number_array);
                }
                if(result_number_array != NULL) free(result_number_array);
            }
            break;

        }
        if(check_number_validation(input_number_array, base) == INVALID_INPUT)
        {
            printf("Ошибка: инвалидное число %s\n", input_number_array);
            if(input_number_array != NULL) free(input_number_array);
            return INVALID_INPUT;
        }
        if(convert_str_to_ll_int(input_number_array, &input_number, base) == INVALID_INPUT)
        {
            printf("Ошибка: невалидное число %s\n", input_number_array);
            if (input_number_array != NULL) free(input_number_array);
            return INVALID_INPUT;
        }

        if(llabs(input_number) - llabs(result_number) > 0)
        {
            result_number = input_number;
        }

        flag_stop = 1;
    }

    if(input_number_array != NULL) free(input_number_array);

    return 0;
}