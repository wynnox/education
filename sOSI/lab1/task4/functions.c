#include "file_processing.h"

enum errors convert_str_to_int (const char *str, unsigned int * result, int base)
{
    char *endptr;
    errno = 0;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && *result == UINT_MAX)
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors xor8_file(FILE* input, unsigned int * result)
{
    *result = 0;
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), sizeof(c), input))
    {
        *result ^= c;
    }
//    if(ferror(input))
//    {
//        return ERROR_READ_FILE;
//    }
    return OK;
}

enum errors xor32_file(FILE* input, unsigned char ** group, size_t size_group)
{
    for(size_t i = 0; i < size_group; ++i)
    {
        (*group)[i] = 0;
    }
    size_t size_buffer = size_group;
    unsigned char* buffer = (unsigned char *)malloc(sizeof(unsigned char) * size_buffer);
    if(buffer == NULL)
    {
        return INVALID_MEMORY;
    }
    for(size_t i = 0; i < size_buffer; ++i)
    {
        buffer[i] = 0;
    }
    while( fread(buffer, sizeof(unsigned char), size_buffer, input) > 0)
    {
        for(size_t i = 0; i < size_group; ++i)
        {
            (*group)[i] ^= buffer[i];
        }
    }
    if(ferror(input))
    {
        free(buffer);
        return ERROR_READ_FILE;
    }
    free(buffer);
    return OK;
}

enum errors count_xor_mask_file(FILE* input, unsigned int mask, unsigned int number, int * count_result)
{
    *count_result = 0;
    number = 0;
    while(fread(&number, sizeof(unsigned int), 1, input) > 0)
    {
        if((number & mask) > 0)
        {
            (*count_result)++;
        }
    }
    if(ferror(input))
    {
        return ERROR_READ_FILE;
    }
    return OK;
}