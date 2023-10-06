#include "file_operations_with_flag.h"

enum errors read_input_from_file_into_array(FILE ** input, char** buff, int* len)
{
    *len = 0;
    char symbol = fgetc(*input);
    while (symbol == ' ' || symbol == '\t' || symbol == '\n')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != EOF)
    {
        (*buff)[(*len)++] = symbol;
        if(*len == 102)
        {
//            if(input != NULL) fclose(*input);
//            free(buff);
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    (*buff)[(*len)] = '\0';
    return OK;
}

void convert_to_lowercase_and_base4(char** array, int len, short ** result)
{
    short number_base4 = 0;
    for(int i = 0; i < len; ++i)
    {
        if(isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
        int temp_num = (int)(*array)[i];
        int base10 = 1;
        while(temp_num > 0)
        {
            number_base4 += (temp_num % 4) * base10;
            base10 *= 10;
            temp_num /= 4;
        }
        (*result)[i] = number_base4;
        number_base4 = 0;
    }
}

void convert_to_lowercase(char** array, int len)
{
    for(int i = 0; i < len; ++i)
    {
        if(isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
    }
}

void convert_to_ascii_base8(char** array, int len, short ** result)
{
    short number_base8 = 0;
    for(int i = 0; i < len; ++i)
    {
        short temp_num = (short)(*array)[i];
        int base10 = 1;
        while(temp_num > 0)
        {
            number_base8 += (temp_num % 8) * base10;
            base10 *= 10;
            temp_num /= 8;
        }
        (*result)[i] = number_base8;
        number_base8 = 0;
    }
}