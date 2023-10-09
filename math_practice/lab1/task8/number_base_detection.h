#ifndef NUMBER_BASE_DETECTION_H_
#define NUMBER_BASE_DETECTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>


enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

enum errors read_write_file(FILE** input, FILE** output);
enum errors convert_str_to_ll_int (const char *str, long long int * result, int base);
enum errors read_input_from_file_into_array(FILE ** input, char** buff, int* len, int* min_base);

#endif