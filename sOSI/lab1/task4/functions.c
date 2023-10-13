#include "file_processing.h"

enum errors xor8_file(FILE* input, unsigned int * result)
{
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), sizeof(c), input))
    {
        *result ^= c;
    }
    if(ferror(input))
    {
        return ERROR_READ_FILE;
    }
    return OK;
}

enum errors xor32_file(FILE* input, unsigned int * result)
{
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), 1, input) > 0)
    {
        *result ^= c;
    }

    if(ferror(input))
    {
        return ERROR_READ_FILE;
    }
    return OK;
}