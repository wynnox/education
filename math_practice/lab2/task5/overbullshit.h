#ifndef OVERBULLSHIT_H_
#define OVERBULLSHIT_H_

enum errors
{
    OK,
    NO_ROOTS,
    OVERFLOW_ERROR,
    INVALID_INPUT,
    ERROR_OPEN_FILE
};

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int oversprintf(char * str, const char * format, ...);

char * Ro(int num);

#endif