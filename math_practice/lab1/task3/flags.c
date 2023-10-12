#include "math_calc_with_flags.h"

enum errors convert_str_to_double (const char *str, long double * result)
{
    char *endptr;
    *result = strtold(str, &endptr);
    if (errno == ERANGE && (*result == HUGE_VALL || *result == -HUGE_VALL))
    {
        return INVALID_INPUT;
    } else if (errno == ERANGE && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

enum errors convert_str_to_int (const char *str, long int * result, int base)
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

int check_overflow_double(long double* num1, long double* num2, long double epsilon)
{
    epsilon *= 1;
    long double result = *num1 * *num2;
    return (result - DBL_MAX <= epsilon && result + DBL_MAX >= epsilon);
}

enum errors check_triangle(long double epsilon, long double side1, long double side2, long double side3, int * result)
{
    if(!check_overflow_double(&side1, &side1, epsilon) || !check_overflow_double(&side2, &side2, epsilon) || !check_overflow_double(&side3, &side3, epsilon))
        return OVERFLOW_ERROR;

    if (side1 <= epsilon || side2 <= epsilon || side3 <= epsilon)
        return INVALID_INPUT;

    if(fabsl(side1 * side1 + side2 * side2 - side3 * side3) <= epsilon ||
       fabsl(side1 * side1 + side3 * side3 - side2 * side2) <= epsilon ||
       fabsl(side2 * side2 + side3 * side3 - side1 * side1) <= epsilon)
        *result = 1;
    else
        *result = 0;

    return OK;

}

void swap(long double* a, long double* b)
{
    long double temp = *a;
    *a = *b;
    *b = temp;
}

int check_duplicate(long double*** result, int size_result, int *count_array, long double* array, long double epsilon)
{
    int count = 0;
    for(int i = 0; i < *count_array; ++i)
    {
        for(int j = 0; j < size_result; ++j)
        {
            if(fabsl((*result)[i][j] - array[j]) < epsilon) count++;
        }
        if(count == size_result) return 1;
        count = 0;
    }
    return 0;
}

enum errors generation_permutation(long double*** result, int size_result, int left, int right, int *count, long double* array, long double epsilon)
{
    enum errors status;
    int i;
    if(left == right)
    {
        if(check_duplicate(result, size_result, count, array, epsilon)) return OK;
        (*result)[*count] = (long double*)malloc(size_result * sizeof(long double));
        if ((*result)[*count] == NULL)
        {
            return INVALID_MEMORY;
        }
        status = OK;
        for (int j = 0; j < size_result; ++j)
        {
            (*result)[*count][j] = array[j];
        }
        (*count)++;
    }
    else
    {
        status = OK;
        for(i = left; i <= right; i++)
        {
            swap(array + left, array + i);
            status = generation_permutation(result, size_result, left + 1, right, count, array, epsilon);
            swap(array + left, array + i);
        }
    }
    return status;
}