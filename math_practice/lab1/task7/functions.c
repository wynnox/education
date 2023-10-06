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