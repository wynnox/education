#include "math_calc_with_flags.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    long int number = 0;
    errno = 0;

    if((argv[1][0] == '-' || argv[1][0] == '\\') && argv[1][2] == '\0')
    {
        char *endptr;
        number = strtol(argv[2], &endptr, 10);

        if (errno == ERANGE && (number == LONG_MAX || number == LONG_MIN)) {
            printf("Переполнение\n");
            return INVALID_INPUT;
        } else if (errno != 0 && number == 0) {
            printf("Ошибка: \n");
            return INVALID_INPUT;
        } else if (*endptr != '\0') {
            printf("Строка не содержит чисел\n");
            return INVALID_INPUT;
        } else {
            printf("Число: %ld\n", number);
        }


        switch (argv[1][1])
        {
            case 'h':
                // что делать с 0?????????????????????
                int* result_h = NULL;
                int size_arr_result_h = 0;
                if (multiple_of_a_number(number, &result_h, &size_arr_result_h) == INVALID_MEMORY)
                {
                    printf("Ошибка: ошибка работы с памятью\n");
                    free(result_h);
                    return INVALID_MEMORY;
                }
                //что вывести если массив пуст?
                for(int i = 0; i < size_arr_result_h; ++i)
                {
                    printf("%d ", result_h[i]);
                }
                free(result_h);
                break;
            case 'p':
                if(!is_prime(number))
                {
                    printf("Число является простым\n");
                }
                else
                {
                    printf("Число является составным\n");
                }
                break;
            case 's':
                //что с отрицательными делать?
                int size_arr_result_s = count_digits(number);
                char* result_s = NULL;

                if(split_number_to_digits(number, &result_s, &size_arr_result_s) == INVALID_MEMORY)
                {
                    printf("Ошибка: ошибка работы с памятью\n");
                    free(result_s);
                    return INVALID_MEMORY;
                }
                for(int i = 0; i < size_arr_result_s; ++i)
                {
                    printf("%c ", result_s[i]);
                }
                printf("\n");
                free(result_s);
                break;
            case 'e':
                printf("ok\n");
                break;
            case 'a':
                long long int result_a = 0;
                if (sum_of_numbers(number, &result_a) == INVALID_MEMORY)
                {
                    printf("Ошибка: произошло переполнение\n");
                    return INVALID_MEMORY;
                }
                printf("%lld\n", result_a);
                break;
            case 'f':
                unsigned long long int result_f = 1;
                if(factorial_of_a_number(number, &result_f) == INVALID_MEMORY)
                {
                    printf("Ошибка: произошло переполнение\n");
                    return INVALID_MEMORY;
                }
                printf("%llu\n", result_f);
                break;
            default:
                printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
                break;
        }
    }
    else
    {
        printf("Ошибка: неверный формат флага");
        return INVALID_INPUT;
    }

    return 0;
}
