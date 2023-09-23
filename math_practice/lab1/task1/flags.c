#include "math_calc_with_flags.h"

int multiple_of_a_number (long int number, int** result, int* size_arr_res)
{
    int capacity = 4;
    *result = (int*)malloc(capacity * sizeof(int));
    if (result == NULL) return INVALID_MEMORY;


    for(int i = 1; i <= 100; ++i)
    {
        if(i % number == 0)
        {
            (*result)[(*size_arr_res)++] = i;
            if(capacity == *size_arr_res)
            {
                capacity *= 2;
                int* for_realloc = realloc(*result, capacity * sizeof(int));
                if (for_realloc == NULL)
                {
                    free(*result);
                    return INVALID_MEMORY;
                }
                *result = for_realloc;
            }
        }
    }


    //возможно стоит добавить уменьшение, если слишком много
    return OK;
}

int is_prime (long int number)
{
    if(number < 0) number *= -1;

    if (number == 1)
        return 0;
    if (number == 2)
        return 0;
    for (int i = 2; i <= floor(sqrt(number)); i++)
    {
        if (number % i == 0)
            return 1;
    }
    return 0;
}

int split_number_to_digits(long int number, char** result, int* size_arr_res)
{
    *result = (char*)malloc(*size_arr_res * sizeof(char));
    if (*result == NULL) return INVALID_MEMORY;

    for(int i = *size_arr_res - 1; i >= 0; --i)
    {
        (*result)[i] = '0' + (number % 10);
        number /= 10;
    }

    return OK;
}


int count_digits(long int number)
{
    int count = 0;
    while(number != 0)
    {
        number /= 10;
        ++count;
    }
    return count;
}

int sum_of_numbers (long int number, long long int * result)
{
    for (int i = 1; i <= number; ++i)
    {
        if(*result > INT_MAX - i || *result < INT_MIN + i) return INVALID_MEMORY;

        *result += i;
    }
    return OK;
}

int factorial_of_a_number (long int number, unsigned long long int* result)
{
    for(long int i = 1; i <= number; ++i)
    {
        if(*result > ULLONG_MAX / i) return INVALID_MEMORY;
        *result *= i;
    }
    return OK;
}