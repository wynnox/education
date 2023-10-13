#include "file_processing.h"

enum errors xor8_file(FILE* input, unsigned int * result)
{
    *result = 0;
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
    *result = 0;
    size_t size_group = 4;
    unsigned char* group = (unsigned char *)malloc(sizeof(unsigned char) * size_group);
    if(group == NULL)
    {
        return INVALID_MEMORY;
    }
    for(size_t i = 0; i < size_group; ++i)
    {
        group[i] = 0;
    }
    int count_read;
    while( (count_read = fread(group, sizeof(unsigned char), size_group, input)) > 0)
    {
        if(count_read != 4)
        {
            for (size_t i = count_read; i < 4; i++)
            {
                group[i] = 0x00;
            }
        }
        *result ^= *(unsigned int*)group;
    }
    if(ferror(input))
    {
        free(group);
        return ERROR_READ_FILE;
    }
    free(group);
    return OK;
}