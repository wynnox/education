#include "math_calc_with_flags.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    errno = 0;

    if( !((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0') ) {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    long int number = 0;
    if(convert_str_to_int(argv[2], &number, 10) != OK)
    {
        printf("Ошибка: невалидное число\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case 'h':

        int* result_h = NULL;
        int size_arr_result_h = 0;
        enum Errors status_h = multiple_of_a_number(number, &result_h, &size_arr_result_h);

        if(status_h == INVALID_MEMORY)
        {
            printf("Ошибка: ошибка работы с памятью\n");
            if(result_h != NULL) free(result_h);
            return INVALID_MEMORY;
        }
        else if (status_h == INVALID_INPUT)
        {
            printf("Ошибка: деление на ноль\n");
            if(result_h != NULL) free(result_h);
            return INVALID_INPUT;
        }

        if(size_arr_result_h == 0)
        {
            printf("Таких чисел нет\n");
        }
        else
        {
            printf("Массив чисел:\n");
            for(int i = 0; i < size_arr_result_h; ++i)
            {
                printf("%d ", result_h[i]);
            }
        }
        if(result_h != NULL) free(result_h);

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

        int size_arr_result_s = (number == 0) ? 1 : log10l(labs(number));
        char* result_s = NULL;
        enum Errors status_s = split_number_to_digits(number, &result_s, &size_arr_result_s);
        if(status_s == INVALID_MEMORY)
        {
            printf("Ошибка: ошибка работы с памятью\n");
            if(result_s != NULL) free(result_s);
            return INVALID_MEMORY;
        }
        for(int i = 0; i < size_arr_result_s; ++i)
        {
            printf("%c ", result_s[i]);
        }
        printf("\n");
        if(result_s != NULL) free(result_s);

        break;

    case 'e':
        if(number > 10 || number < 0)
        {
            printf("Ошибка: некорректное число\n");
            return INVALID_INPUT;
        }

        long int** result_e = NULL;
        if (table_of_degrees(&result_e, number) == INVALID_MEMORY)
        {
            printf("Ошибка: ошибка работы с памятью\n");
            //тут ничего не делаем, я там очистила
            return INVALID_MEMORY;
        }


        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j <= number; ++j)
            {
                printf("%d^%d = %ld\n", i, j, result_e[i][j]);
            }
            printf("\n");
        }

        for(int i = 0; i < 10; ++i) if(result_e[i] != NULL) free(result_e[i]);
        if(result_e != NULL) free(result_e);

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

    return 0;
}
