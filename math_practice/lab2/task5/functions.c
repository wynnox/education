#include "overbullshit.h"

//Это число получается из максимального числа 3888,
// которое в римской системе счисления представляется как
// "MMMDCCCLXXXVIII". Эта строка содержит 15 символов.
char * Ro(int num)
{
    if(num > 3999 || num < 1)
    {
        return NULL;
    }

    char* roman = (char *)malloc(sizeof(char) * 16);
    if (roman == NULL)
    {
        return NULL;
    }

    roman[0] = '\0';

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < 13; i++)
    {
        while (num >= values[i])
        {
            strcat(roman, symbols[i]);
            num -= values[i];
        }
    }

    return roman;
}


char *Cv(int number, int base, char * array_base)
{
    if(base <  2 || base > 36)
    {
        base = 10;
    }

    int capacity = 20;
    char * result = (char*) malloc(sizeof(char) * capacity);
    if(result == NULL) return NULL;

    int i = 0;
    int flag_negitive = 0;
    if(number < 0)
    {
        result[0] = '-';
        number *= -1;
        ++i;
        flag_negitive = 1;
    }

    while (number > 0)
    {
        int temp = number % base;
        number /= base;
        result[i++] = (char)array_base[temp];
        if(i == capacity)
        {
            char * for_realloc = NULL;
            capacity *= 2;
            for_realloc = (char *)realloc(result, capacity);
            if(for_realloc == NULL)
            {
                free(result);
                return NULL;
            }
            result = for_realloc;
        }
    }

    int start = flag_negitive ? 1 : 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    result[i] = '\0';
    return result;
}

char* dump_memory(void* input, int size)
{
    char* res = (char*)malloc(sizeof(char) * size * 10);
    if (res == NULL)
        return NULL;
    int sz = 0;
    char* pt = (char*) input;
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            char bit = (((*(pt+i)) >> j) & 1) == 0 ? '0' : '1';
            res[sz++] = bit;
        }
        res[sz++] = ' ';
    }
    sz--;
    res[sz] = '\0';
    return res;
}

enum errors To(char * number, int base, int * result_number)
{
    if(base <  2 || base > 36)
    {
        base = 10;
    }

    int len = strlen(number);
    int flag_negative = 0;
    int stop = 0;
    if(number[0] == '-')
    {
        flag_negative = 1;
        stop = 1;
    }
    *result_number = 0;
    for(int i = len - 1; i >= stop; --i)
    {
        int digit;
        if(isdigit(number[i]))
            digit = number[i] - '0';
        else
            digit = toupper(number[i]) - 'A' + 10;

        if(digit >= base) return INVALID_INPUT;

        *result_number += digit * pow(base, len - 1 - i);
    }
    if(flag_negative) *result_number *= -1;
    return OK;
}

char* Zeckendorf(unsigned int num)
{
    unsigned int arr_max_size = 16;
    unsigned int* fib = (unsigned int*)malloc(sizeof(unsigned int) * arr_max_size);
    if (fib == NULL) {
        return NULL;
    }

    fib[0] = 0;
    fib[1] = 1;
    unsigned int ind = 1;
    while (fib[ind] < num)
    {
        ind++;
        if (ind > arr_max_size) {
            arr_max_size *= 2;
            unsigned int* tmp = (unsigned int*)realloc(fib, arr_max_size);
            if (tmp == NULL)
            {
                free(fib);
                return NULL;
            }
            fib = tmp;
        }
        fib[ind] = fib[ind-1] + fib[ind-2];
    }

    unsigned int num1 = num;
    for (int i = ind; i > 0; i--)
    {
        int razn = num1 - fib[i];
        if (razn >= 0) {
            num1 -= fib[i];
            fib[i] = 0;
        }
        if (num1 == 0) {
            break;
        }
    }

    char* ans = (char*)malloc(sizeof(char) * (ind + 3));
    if (ans == NULL)
    {
        free(fib);
        return NULL;
    }
    for (unsigned int i = 0; i <= ind; i++)
    {
        ans[i] = (fib[i] == 0) ? '1' : '0';
    }
    if (ans[ind] == '0')
    {
        ans[ind] = '1';
        ans[ind+1] = '\0';
    }
    else
    {
        ans[ind+1] = '1';
        ans[ind+2] = '\0';
    }

    free(fib);
    return ans;
}


