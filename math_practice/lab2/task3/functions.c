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

enum errors add_sub(struct Sub ** head, char * filename, int line, int idx, int * len)
{
    struct Sub * new_sub = (struct Sub *)malloc(sizeof(struct Sub));
    if(new_sub == NULL)
    {
        return INVALID_MEMORY;
    }

    int len_filename = string_len(filename);
    new_sub->filename = (char *)malloc(sizeof(char) * (len_filename + 1));
    if(new_sub->filename == NULL)
    {
        return INVALID_MEMORY;
    }

    for(int i = 0; i < len_filename; ++i)
    {
        new_sub->filename[i] = filename[i];
    }
    new_sub->filename[len_filename] = '\0';

    new_sub->idx = idx;
    new_sub->line = line;
    if(idx == -1 && line == -1)
    {
        new_sub->flag_open = 0;
    }
    else
    {
        new_sub->flag_open = 1;
    }
    new_sub->next = NULL;

    if(*head == NULL)
    {
        *head = new_sub;
    }
    else
    {
        struct Sub * current = *head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_sub;
    }
    (*len)++;
    return OK;
}


enum errors find_substring_in_file(struct Sub ** subs, char * str, int * len_subs, int count_file, ...)
{
    if(count_file <= 0)
    {
        return INVALID_INPUT;
    }
    va_list args;
    va_start(args, count_file);

    *len_subs = 0;

    for (int i = 0; i < count_file; ++i)
    {
        char * filepath = va_arg(args, char*);
        FILE * input = fopen(filepath, "r");
        if(input == NULL)
        {
            if(add_sub(subs, filepath, -1, -1, len_subs) != OK)
            {
                return INVALID_MEMORY;
            }
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
                if(add_sub(subs, filepath, count_line_output, count_char_output, len_subs) != OK)
                {
                    return INVALID_MEMORY;
                }
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
