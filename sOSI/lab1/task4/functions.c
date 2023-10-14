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
    if(ferror(input))
    {
        return ERROR_READ_FILE;
    }
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
    int count_read;
    while( (count_read = fread(buffer, sizeof(unsigned char), size_buffer, input)) > 0)
    {
        if(count_read != 4)
        {
            for (size_t i = count_read; i < 4; i++)
            {
                buffer[i] = 0x00;
            }
        }
        for(size_t i = 0; i < size_group; ++i)
        {
            (*group)[i] ^= buffer[i];
        }
    }
    if(ferror(input))
    {
        free(group);
        return ERROR_READ_FILE;
    }
    free(buffer);
    return OK;
}

enum errors count_xor_mask_file(FILE* input, unsigned int * mask, int * count_result)
{
    *count_result = 0;

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
        if( *(unsigned int*)group == *mask)
        {
            (*count_result)++;
        }
        printf("mask: ");
        for (size_t i = 0; i < size_group; ++i)
        {
            printf("%u ", group[i]);
        }
        printf("\ngroup: %u\n", *(unsigned int*)group);
    }
    if(ferror(input))
    {
        free(group);
        return ERROR_READ_FILE;
    }
    free(group);
    return OK;
}