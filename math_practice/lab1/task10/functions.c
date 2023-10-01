#include "number_conversion.h"

enum errors convert_str_to_ll_int (const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
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
    //size_t len = 0;
    for(int i = 0; number[i] != '\0'; ++i)
    {
        if(number[0] == '-') continue;
        else if((number[i] >= '0' && number[i] <= '9') && (number[i] - '0') < base);
        else if((number[i] >= 'A' && number[i] <= 'Z') && (number[i] - 55) < base);
        else return INVALID_INPUT;
    }

    return OK;
}

void converting_number_to_array(long long int number, char** result)
{
    if (number < 0)
    {
        (*result)[0] = '-';
        number = llabs(number);
    }
}

//enum Errors split_number_to_digits(long int number, char** result, int* size_arr_res)
//{
//    (*size_arr_res)++;
//    *result = (char*)malloc((*size_arr_res + 1) * sizeof(char));
//    if (*result == NULL) return INVALID_MEMORY;
//
//    if (number < 0)
//    {
//        (*result)[0] = '-';
//        number = labs(number);
//    }
//
//    for(int i = *size_arr_res - 1; i >= 0; --i)
//    {
//        (*result)[i + 1] = '0' + (number % 10);
//        number /= 10;
//    }
//
//    (*size_arr_res)++;
//    return OK;
//}