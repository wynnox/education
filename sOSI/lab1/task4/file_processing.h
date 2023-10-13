#ifndef FILE_PROCESSING_H_
#define FILE_PROCESSING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    ERROR_READ_FILE
};

enum errors xor8_file(FILE* input, unsigned int * result);
enum errors xor32_file(FILE* input, unsigned int * result);

#endif