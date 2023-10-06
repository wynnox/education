#ifndef FILE_OPERATIONS_WITH_FLAG_H_
#define FILE_OPERATIONS_WITH_FLAG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

enum errors read_input_from_file_into_array(FILE ** input, char** buff, int* len);


#endif