#include "math_calc_with_flags.h"

enum Errors convert_str_to_int (const char *str, long int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors multiple_of_a_number (long int number, int** result, int* size_arr_res)
{
    if(number == 0) return INVALID_INPUT;

    int capacity = 4;
    *result = (int*)malloc(capacity * sizeof(int));
    if (result == NULL) return INVALID_MEMORY;


    for(int i = 1; i <= 100; ++i) {
        if (i % number == 0) {
            (*result)[(*size_arr_res)++] = i;
            if (capacity == *size_arr_res) {
                capacity *= 2;
                int *for_realloc = realloc(*result, capacity * sizeof(int));
                if (for_realloc == NULL) {
                    //free(*result);
                    return INVALID_MEMORY;
                }
                *result = for_realloc;
            }
        }
    }
    return OK;
}

int is_prime (long int number)
{
    if(number < 0) number *= -1;

    if (number == 0 || number == 1 || number == 2)
        return 0;

    if(number % 2 == 0) return 1;

    for (int i = 3; i <= floor(sqrt(number)); i++)
    {
        if (number % i == 0)
            return 1;
    }
    return 0;
}

enum Errors split_number_to_digits(long int number, char** result, int* size_arr_res)
{
    (*size_arr_res)++;
    *result = (char*)calloc((*size_arr_res + 1), sizeof(char));
    if (*result == NULL) return INVALID_MEMORY;

    if (number < 0)
    {
        (*result)[0] = '-';
        number = labs(number);
    }

    for(int i = *size_arr_res - 1; i >= 0; --i)
    {
        (*result)[i + 1] = '0' + (number % 10);
        number /= 10;
    }

    (*size_arr_res)++;
    return OK;

}

enum Errors table_of_degrees(long int*** result, long int number)
{

    *result = (long int **) malloc(11 * sizeof(long int*));
    if((*result) == NULL) return INVALID_MEMORY;

    for (int i = 0; i <= 10; ++i)
    {
        (*result)[i] = (long int *) malloc((number + 1) * sizeof(long int));

        if((*result)[i] == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free((*result)[j]);
            }
            free(*result);
            return INVALID_MEMORY;
        }
    }

    (*result)[0][0] = 1;
    for(int i = 1; i < 11; ++i)
    {
        (*result)[i][0] = 1;
        (*result)[i][1] = i;
    }

    for(int base = 2; base <= 10; ++base)
    {
        for(int degree = 2; degree <= number; ++degree)
        {
            (*result)[base][degree] = (*result)[base][degree - 1] * base;
        }
    }

    return OK;

}

enum Errors sum_of_numbers (long int number, long long int * result)
{
    int flag = 1;
    if (number < 0)
    {
        number = labs(number);
        flag = -1;
    }
    for (int i = 1; i <= number; ++i)
    {
        if(*result > INT_MAX - i || *result < INT_MIN + i) return INVALID_MEMORY;

        *result += i;
    }
    *result = *result * flag;
    return OK;
}

enum Errors factorial_of_a_number (long int number, unsigned long long int* result)
{
    for(long int i = 1; i <= number; ++i)
    {
        if(*result > ULLONG_MAX / i) return INVALID_MEMORY;
        *result *= i;
    }
    return OK;
}