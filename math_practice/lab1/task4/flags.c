#include "file_operations_with_flag.h"

void remove_arabic_numerals(FILE* input, FILE* output)
{
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        if (c >= '0' && c <= '9') continue;
        fputc(c, output);
    }
}

void counter_latin_letter(FILE* input, FILE* output)
{
    int c;
    long int counter_of_str = 1, counter_of_letter = 0;
    while (!feof(input))
    {
        c = fgetc(input);
        if (c == EOF)
        {
            fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
        }
        if(c == '\n')
        {
            fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
            counter_of_str++;
            counter_of_letter = 0;
        }
        else if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            counter_of_letter++;
        }
    }
//    if(counter_of_letter != 0)
//        fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
}

void counter_character(FILE* input, FILE* output)
{
    int c;
    long int counter_of_str = 1, counter_of_letter = 0;
    while (!feof(input))
    {
        c = fgetc(input);
        if (c == EOF)
        {
            fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
        }
        if (isalnum(c) || c == ' ')
            continue;
        else if (c == '\n')
        {
            fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
            counter_of_str++;
            counter_of_letter = 0;
        }
        else
        {
            counter_of_letter++;
        }
    }
//    if(counter_of_letter != 0)
//        fprintf(output, "%ld. %ld\n", counter_of_str, counter_of_letter);
}

void replacing_numbers(FILE* input, FILE* output)
{
    int c;
    while ((c = fgetc(input)) != EOF)
    {
        if ((c >= '0' && c <= '9' )|| c == '\n') fputc(c, output);
        else fprintf(output, "%X", c);
    }
}
