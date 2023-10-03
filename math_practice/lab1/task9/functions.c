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

enum errors array_generation_of_task2(int start_for_generation, int end_for_genetation, short ** result_array, int size_of_array)
{
    (*result_array) = (short *) malloc(size_of_array * sizeof(short));
    if ((*result_array) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(time(NULL));
    for(int i = 0; i < size_of_array; ++i)
    {
        int num;
        do {
            num = rand();
        } while (num < start_for_generation || num > end_for_genetation);
        (*result_array)[i] = (short)num;
        //(*result_array)[i] = (short )(rand() % (labs(end_for_genetation) + 1 - labs(start_for_generation)) + start_for_generation);
    }
    return OK;
}

enum errors generate_array_and_find_closest(short ** array_a, int size_of_array_a,
                                            short ** array_b, int size_of_array_b,
                                            short ** array_c)
{
    (*array_c) = (short*) malloc(sizeof(short) * size_of_array_a);
    if(array_c == NULL)
    {
        free(array_a);
        free(array_b);
        return INVALID_MEMORY;
    }
    for(int i = 0; i < size_of_array_a; ++i)
    {
        (*array_c)[i] = (*array_a)[i] + find_number(array_b, size_of_array_b, (*array_a)[i]);
    }

    return OK;
}

int find_number(short ** array, int size_of_array, short number)
{
    int result = (*array)[0];
    int min_diff = labs((*array)[0] - number);
    number = labs(number);
    for(int i = 1; i < size_of_array; i++) {
        int diff = labs(labs((*array)[i]) - number);
        if(diff < min_diff) {
            min_diff = diff;
            result = (*array)[i];
        }
    }
    return result;
}