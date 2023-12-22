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
#include <errno.h>
#include <math.h>
#include <ctype.h>


int oversprintf(char * str, const char * format, ...);
int overfprintf(FILE* stream, char* format, ...);

char * Ro(int num);
char * Cv(int number, int base, char * array_base);
enum errors To(char * number, int base, int * result_number);
char* Zeckendorf(unsigned int num);
char* dump_memory(void* input, int size);



#endif