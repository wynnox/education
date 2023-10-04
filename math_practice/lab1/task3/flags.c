#include "math_calc_with_flags.h"

enum Errors convert_str_to_double (const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0' || (*result == 0 && errno == ERANGE))
    {
        return INVALID_INPUT;
    }
    return OK;
}

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

int check_overflow_double(double* num, double epsilon)
{
    return fabs(*num - fabs(DBL_MAX / *num)) > epsilon;
}

enum Errors check_triangle(double epsilon, double side1, double side2, double side3, int * result)
{
    if(!check_overflow_double(&side1, epsilon) || !check_overflow_double(&side2, epsilon) || !check_overflow_double(&side3, epsilon))
        return OVERFLOW_ERROR;

    if (side1 <= epsilon || side2 <= epsilon || side3 <= epsilon)
        return INVALID_INPUT;

    if(fabs(side1 * side1 + side2 * side2 - side3 * side3) <= epsilon ||
       fabs(side1 * side1 + side3 * side3 - side2 * side2) <= epsilon ||
       fabs(side2 * side2 + side3 * side3 - side1 * side1) <= epsilon)
        *result = 1;
    else
        *result = 0;

    return OK;

}

void swap(double * a, double * b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(double *** result, double* array, int size_array, int* count, int n, double epsilon)
{
//    if(count == 0)
//    {
//        for(int i = 0; i < size_array; i++)
//        {
//            (*result)[*count][i] = array[i];
//        }
//        (*count)++;
//        return;
//    }
    if (n == 1) {
//        if(!is_duplicate(result, array, size_array, *count, epsilon))
//        {
//            (*count)++;
//            for(int i = 0; i < size_array; i++)
//            {
//                (*result)[*count][i] = array[i];
//            }
//        }
        (*count)++;
        for(int i = 0; i < size_array; i++)
        {
            (*result)[*count][i] = array[i];
        }
        printf("я тут\n");
        return;
    }

    for(int i = 0; i < n; ++i)
    {
        permutation(result, array, size_array, count, n - 1, epsilon);

        if(n % 2 == 1)
        {
            swap(&(array[0]), &array[n - 1]);
        }
        else
        {
            swap(&array[i], &array[n - 1]);
        }
    }
}

int is_duplicate(double *** result, double* array, int size_array, int count, double epsilon)
{
    for(int i = 0; i < count; ++i)
    {
        int flag = 1;
        for(int j = 0; j < size_array; ++j)
        {
            if (i < count && fabs((*result)[i][j] - array[j]) > epsilon) {
                flag = 0;
                break;
            }
        }
        if(flag) return 1;
    }
    return 0;
}