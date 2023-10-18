#include "string_operations_with_flag.h"

int string_len(const char * str)
{
    size_t len = 0;
    while (*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}

enum errors string_reverse(const char * str, char ** result)
{
    int len = string_len(str);
    (*result) = (char *)malloc(sizeof(char) * (len + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    int j = 0;
    --len;
    while(len >= 0)
    {
        (*result)[j++] = str[len--];
    }
    (*result)[j] = '\0';
    return OK;
}

enum errors convert_odd_chars_to_upper(const char * str, char ** result)
{
    int len = string_len(str);
    (*result) = (char *)malloc(sizeof(char) * (len + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    for(int i = 0; i < len; ++i)
    {
        if(i % 2 != 0 && str[i] >= 'a' && str[i] <= 'z')
        {
            (*result)[i] = str[i] - 32;
        }
        else
        {
            (*result)[i] = str[i];
        }
    }
    (*result)[len] = '\0';
    return OK;
}

enum errors reorder_string(const char * str, char ** result)
{
    int len = string_len(str);
    (*result) = (char *)malloc(sizeof(char) * (len + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    int idx = 0;
    for(int i = 0; i < len; ++i)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            (*result)[idx++] = str[i];
        }
    }
    for(int i = 0; i < len; ++i)
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[idx++] = str[i];
        }
    }
    for(int i = 0; i < len; ++i)
    {
        if( !(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'a' && str[i] <= 'z') &&
            !(str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[idx++] = str[i];
        }
    }
    (*result)[idx] = '\0';
    return OK;
}

enum errors convert_str_to_int (const char *str, unsigned int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == UINT_MAX|| *result == 0))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors concatenate_randomly(char ** strs, int count_str, char ** result, unsigned int seed)
{
    int len = 0, capacity = 0;
    for(int i = 0; i < count_str; ++i)
    {
        len = string_len(strs[i]);
        if (len > capacity) capacity = len;
    }
    capacity *= count_str;
    len = 0;
    (*result) = (char *)malloc(sizeof(char) * (capacity + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(seed);
    int rand_num;
    for(int i = 0; i < count_str; ++i)
    {
        rand_num = rand() % count_str;
        concat_string(strs[rand_num], result, &len);
    }
    return OK;
}

void concat_string(char * str, char ** result, int * len)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        (*result)[(*len)++] = str[i];
    }
    (*result)[(*len)] = '\0';
}