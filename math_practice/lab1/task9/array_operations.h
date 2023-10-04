#ifndef ARRAY_OPERATIONS_H_
#define ARRAY_OPERATIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

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


enum errors array_generation_of_task2(int start_for_generation, int end_for_genetation,
                                      short ** result_array, int size_of_array);
enum errors generate_array_and_find_closest(short ** array_a, int size_of_array_a,
                                            short ** array_b, int size_of_array_b,
                                            short ** array_c);
int find_number(short ** array, int size_of_array, short number);
void bubble_sort(short** arr, int size);
short find_closest(short ** array, int size, short number);

#endif