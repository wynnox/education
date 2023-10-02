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
                int * base_array_for_print = (int*)malloc(5 * sizeof(int));
                if(base_array_for_print == NULL)
                {
                    printf("Ошибка: ошибка работы с памятью\n");
                    return INVALID_MEMORY;
                }
                base_array_for_print[0] = base;
                base_array_for_print[1] = 9;
                base_array_for_print[2] = 18;
                base_array_for_print[3] = 27;
                base_array_for_print[4] = 36;

                for(int i = 0; i < 5; ++i)
                {
                    if(convert_to_base(&result_number_array, result_number, base_array_for_print[i], array_base) != OK)
                    {
                        printf("Ошибка: я хз как на этом этапе может вылезти ошибка, наверн с памятью что-то\n");
                        free(input_number_array);
                        free(result_number_array);
                        free(base_array_for_print);
                        return INVALID_MEMORY;
                    }
                    printf("%d: %s\n", base_array_for_print[i], result_number_array);
                    free(result_number_array);
                    result_number_array = NULL;
                }
                free(base_array_for_print);
            }
            break;

        }
        if(check_number_validation(input_number_array, base) == INVALID_INPUT)
        {
            printf("Ошибка: инвалидное число %s\n", input_number_array);
            free(input_number_array);
            return INVALID_INPUT;
        }
        if(convert_str_to_ll_int(input_number_array, &input_number, base) == INVALID_INPUT)
        {
            printf("Ошибка: невалидное число %s\n", input_number_array);
            free(input_number_array);
            return INVALID_INPUT;
        }

        if(llabs(input_number) - llabs(result_number) > 0)
        {
            result_number = input_number;
        }

        flag_stop = 1;
    }

    free(input_number_array);

    return 0;
}