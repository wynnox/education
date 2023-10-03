#include "array_operations.h"

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

enum errors array_generation(long int start_for_generation,
                      long int end_for_genetation,
                      long int ** result_array,
                      int size_of_array)
{
    (*result_array) = (long int *) malloc(size_of_array * sizeof(long int));
    if ((*result_array) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(time(NULL));
    for(int i = 0; i < size_of_array; ++i)
    {
        (*result_array)[i] = rand() % (labs(end_for_genetation) + 1 - labs(start_for_generation)) + start_for_generation;
    }

    return OK;
}

void swap_min_max_in_array(long int ** array, int size_of_array)
{
    int min_ind = 0;
    int max_ind = 0;
    for(int i = 0; i < size_of_array; ++i)
    {
        if((*array)[i] < (*array)[min_ind]) min_ind = i;
        if((*array)[i] > (*array)[max_ind]) max_ind = i;
    }
    long int temp = (*array)[max_ind];
    (*array)[max_ind] = (*array)[min_ind];
    (*array)[min_ind] = temp;
}