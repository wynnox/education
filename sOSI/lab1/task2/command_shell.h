#ifndef COMMAND_SHELL_H_
#define COMMAND_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 20

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    EMPTY_FILE
};

typedef struct {
    char login[7];
    int pin;
    int limit_request;
} User;

enum errors reading_users_from_file(FILE * input_file, User * user_data, int* count_users, int * capacity_user_data);
enum errors registration_or_authorization(FILE * output_file, User * user_data,
        int* count_users, int * capacity_user_data, int * index_user, int * flag_empty_file);
void command();
void writing_users_in_file(FILE * input_file, User * user_data, int* count_users);

#endif