#include "sum_in_base.h"
/*
 * 3) сложение
 * 4) обратный реверс результата
 */

enum errors sum_in_base(char ** result, int base, int count_number, ...)
{
    if(count_number <= 0 || (base < 2 || base > 36))
    {
        return INVALID_INPUT;
    }

    int capacity_res = LEN, len_res = 0;
    (*result) = (char *)calloc(sizeof(char), capacity_res);
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }

    va_list args;
    va_start(args, count_number);
    for (int i = 0; i < count_number; ++i)
    {
        char * number_arg = va_arg(args, char*);
        char * number = strdup(number_arg);
        if(check_valid(base, &number))
        {
            printf("number %s is incorrect\n", number);
            va_end(args);
            free(number);
            return INVALID_INPUT;
        }
        int len_num = strlen(number);
        reverse(&number, len_num);
        if(len_num + 1 > capacity_res || len_res + 1 > capacity_res)
        {
            capacity_res *= 2;
            char ** for_realloc = (char **)realloc((*result), capacity_res);
            if(for_realloc == NULL)
            {
                va_end(args);
                free(number);
                return INVALID_MEMORY;
            }
            result = for_realloc;
        }
        sum_of_numbers(result, number, base, &len_res, len_num);
        free(number);
    }
    while(len_res > 1 && (*result)[len_res - 1] == '0')
    {
        (*result)[--len_res] = '\0';
    }
    reverse(result, len_res);
    va_end(args);
    return OK;
}

int check_valid(int base, char ** number)
{
    if((*number)[0] == '\0')
    {
        return 1;
    }
    for(int i = 0; (*number)[i] != '\0'; ++i)
    {
        if(isdigit((*number)[i]))
        {
            if( (*number)[i] - '0'>= base)
            {
                return 1;
            }
        }
        else if(isalpha((*number)[i]))
        {
            (*number)[i] = (char)toupper((*number)[i]);
            if((*number)[i]  - 'A' + 10 >= base)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void reverse(char ** number, int len)
{
    int i = 0, j = len - 1;
    for(; (j - i) > 0; ++i, --j)
    {
        char temp = (*number)[i];
        (*number)[i] = (*number)[j];
        (*number)[j] = temp;
    }
}

void sum_of_numbers(char ** result, char * number, int base, int * len_res, int len_num)
{
    int len_sum = (*len_res > len_num) ? len_num : *len_res;
    int next_digit = 0;
    int idx = 0;
    for(; idx < len_sum; ++idx)
    {
        int n1 = isdigit((*result)[idx]) ? (*result)[idx] - '0' : (*result)[idx] - 'A' + 10;
        int n2 = isdigit(number[idx]) ? number[idx] - '0' : number[idx] - 'A' + 10;
        int sum = n1 + n2  + next_digit;
        (*result)[idx] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
        next_digit = sum / base;
    }
    if(*len_res > len_num)
    {
        for(; idx < *len_res; ++idx)
        {
            int n1 = isdigit((*result)[idx]) ? (*result)[idx] - '0' : (*result)[idx] - 'A' + 10;
            int sum = n1 + next_digit;
            (*result)[idx] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
            next_digit = sum / base;
        }
    }
    if(len_num > *len_res)
    {
        for(; idx < len_num; ++idx)
        {
            int n2 = isdigit(number[idx]) ? number[idx] - '0' : number[idx] - 'A' + 10;
            int sum = n2 + next_digit;
            (*result)[idx] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
            next_digit = sum / base;
        }
    }
    if(next_digit != 0)
    {
        (*result)[idx++] = next_digit > 9 ? next_digit + 'A' - 10 : next_digit + '0';
    }
    (*result)[idx] = '\0';
    *len_res = idx;
}