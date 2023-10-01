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
//    char * array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char * result_array = NULL;
    char * input_number_array = NULL;

    input_number_array = malloc(sizeof(char) * 101);
    if(input_number_array == NULL)
    {
        printf("Ошибка: ошибка работы с памятью\n");
        return INVALID_MEMORY;
    }

    long long int result_number = 0;
    long long int input_number = 0;
    int flag_stop = 1;
    while(scanf("%100s", input_number_array))
    {
        if(strcmp(input_number_array, end_of_input) == 0)
        {
            if(flag_stop) break;

        }
        if(check_number_validation(input_number_array, base) == INVALID_INPUT)
        {
            printf("Ошибка: инвалидное число %s\n", input_number_array);
            free(input_number_array);
            //free(result);
            return INVALID_INPUT;
        }
        if(convert_str_to_ll_int(input_number_array, &input_number, base) == INVALID_INPUT)
        {
            printf("Ошибка: невалидное число %s\n", input_number_array);
            free(input_number_array);
            //free(result);
            return INVALID_INPUT;
        }

        if(llabs(input_number) - llabs(result_number) > 0)
        {
            result_number = input_number;
        }

        int flag_stop = 0;
    }


    return 0;
}