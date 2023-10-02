#include "number_conversion.h"

enum errors convert_str_to_ll_int (const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (errno == ERANGE && (*result == LLONG_MAX || *result == LLONG_MIN))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors check_number_validation(char * number, int base)
{
    for(int i = 0; number[i] != '\0'; ++i)
    {
        if(number[0] == '-') continue;
        else if((number[i] >= '0' && number[i] <= '9') && (number[i] - '0') < base);
        else if((number[i] >= 'A' && number[i] <= 'Z') && (number[i] - 55) < base);
        else return INVALID_INPUT;
    }

    return OK;
}

enum errors convert_to_base(char ** result, long long int number, int base, char * array_base)
{
    int capacity = 20;
    (*result) = (char*) malloc(sizeof(char) * capacity);
    if(*result == NULL) return INVALID_MEMORY;

    int i = 0;
    int flag_negitive = 0;
    if(number < 0)
    {
        (*result)[0] = '-';
        number *= -1;
        ++i;
        flag_negitive = 1;
    }

    while (number > 0)
    {
        int temp = number % base;
        if(temp >= base)
        {
            free(result);
            return INVALID_INPUT;
        }
        number /= base;
        (*result)[i++] = (char)array_base[temp];
        if(i == capacity)
        {
            char ** for_realloc = NULL;
            capacity *= 2;
            for_realloc = (char **) realloc(result, capacity);
            if(for_realloc == NULL)
            {
                free(result);
                return INVALID_MEMORY;
            }
            result = for_realloc;
        }
    }

    int start = flag_negitive ? 1 : 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = (*result)[start];
        (*result)[start] = (*result)[end];
        (*result)[end] = temp;
        start++;
        end--;
    }

    (*result)[i] = '\0';
    return OK;
}