#include "number_base_detection.h"

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

enum errors read_input_from_file_into_array(FILE ** input, char** buff, int* len, int* min_base)
{
    *len = 0;
    *min_base = 2;
    char symbol = fgetc(*input);
    int flag_negative = 0;
    int flag_skip = 0;
    while (symbol == ' ' || symbol == '\t' || symbol == '\n')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != EOF)
    {
        if(symbol == '-' && *len == 0)
        {
            (*buff)[(*len)++] = symbol;
            flag_negative = 1;
        }
        else if ( (symbol == '0' && *len == 0) || (symbol == '0' && *len == 1 && flag_negative == 1) )
        {
            symbol = fgetc(*input);
            flag_skip = 1;
            continue;
        }
        else if(isdigit(symbol))
        {
            (*buff)[(*len)++] = symbol;
            if( symbol - '0' + 1 > *min_base)
            {
                *min_base = symbol - '0' + 1;
            }
        }
        else if(isalpha(symbol))
        {
            (*buff)[(*len)++] = (char)toupper(symbol);
            if(toupper(symbol) - 'A' + 1 > *min_base)
            {
                *min_base = toupper(symbol) - 'A' + 10 + 1;
            }
        }
        else
        {
            return INVALID_INPUT;
        }
        if(*len == 201)
        {
//            if(input != NULL) fclose(*input);
//            free(buff);
            return INVALID_INPUT;
        }
        if(*min_base > 36)
        {
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    if(*len == 0 && flag_skip) (*buff)[(*len)++] = '0';
    (*buff)[(*len)] = '\0';
    return OK;
}