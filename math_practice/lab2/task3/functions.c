#include "find_substring_in_file.h"

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

enum errors find_substring_in_file(char * str, int count_file, ...)
{
    if(count_file <= 0)
    {
        return INVALID_INPUT;
    }
    va_list args;
    va_start(args, count_file);

    for (int i = 0; i < count_file; ++i)
    {
        char * filepath = va_arg(args, char*);
        FILE * input = fopen(filepath, "r");
        if(input == NULL)
        {
            printf("the file %s did not open\n", filepath);
            continue;
        }

        int count_line = 1, idx = 0, count_char = 0;
        int count_line_output, count_char_output;
        int len_str = string_len(str);
        char c;
        while(!feof(input))
        {
            c = fgetc(input);
            if(str[idx] == c)
            {
                if(idx == 0)
                {
                    count_char_output = count_char;
                    count_line_output = count_line;
                }
                idx++;
            }
            else
            {
                idx = 0;
            }
            if(idx == len_str)
            {
                printf("file:%s, №%d: idx:%d\n", filepath, count_line_output, count_char_output);
                idx = 0;
            }
            count_char++;
            if(c == '\n')
            {
                count_line++;
                count_char = 0;
            }
        }
        fclose(input);
    }
    va_end(args);
    return OK;
}