#ifndef ARRAY_OPERATIONS_H_
#define ARRAY_OPERATIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY
};

enum errors convert_str_to_int (const char *str, long int * result, int base);
enum errors array_generation(long int start_for_generation,
                             long int end_for_genetation,
                             long int ** result_array,
                             int size_of_array);
void swap_min_max_in_array(long int ** array, int size_of_array);

#endif