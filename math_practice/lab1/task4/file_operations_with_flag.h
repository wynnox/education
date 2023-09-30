#ifndef FILE_OPERATIONS_WITH_FLAG_H_
#define FILE_OPERATIONS_WITH_FLAG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum Errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

void remove_arabic_numerals(FILE* input, FILE* output);
void counter_latin_letter(FILE* input, FILE* output);
void counter_character(FILE* input, FILE* output);
void replacing_numbers(FILE* input, FILE* output);

#endif