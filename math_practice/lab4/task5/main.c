#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "ctype.h"

#define SIZE 20

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    DIVISION_BY_ZERO,
    EMPTY_LINE,
    EMPTY_BRACKET,
    INVALID_BRACKET
};

typedef struct Stack_char
{
    char value;
    struct Stack_char * next;
} Stack_char;

typedef struct Stack_number
{
    long long value;
    struct Stack_number * next;
} Stack_number;

enum errors Stack_char_push(Stack_char ** head, char data)
{
    Stack_char * tmp = (Stack_char*) malloc(sizeof(Stack_char));
    if(tmp == NULL)
    {
        return INVALID_MEMORY;
    }
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
    return OK;
}

enum errors Stack_char_pop(Stack_char ** head, char * num)
{
    Stack_char* prev = NULL;
    if (head == NULL || *head == NULL)
    {
        return INVALID_INPUT;
    }

    prev = (*head);
    *num = prev->value;
    (*head) = (*head)->next;

    free(prev);
    return OK;
}

void Stack_char_free(Stack_char * head)
{
    Stack_char * tmp = NULL;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

enum errors Stack_number_push(Stack_number ** head, long long data)
{
    Stack_number * tmp = (Stack_number*) malloc(sizeof(Stack_number));
    if(tmp == NULL)
    {
        return INVALID_MEMORY;
    }
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
    return OK;
}

enum errors Stack_number_pop(Stack_number ** head, long long * num)
{
    Stack_number* prev = NULL;
    if (head == NULL || *head == NULL)
    {
        return INVALID_INPUT;
    }

    prev = (*head);
    *num = prev->value;
    (*head) = (*head)->next;

    free(prev);
    return OK;
}

void Stack_number_free(Stack_number * head)
{
    Stack_number * tmp = NULL;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

enum errors convert_str_to_long_long(const char * str, long long * result, int base)
{
    char * endptr;
    long long num = strtoll(str, &endptr, base);

    if ((errno == ERANGE && (num == LLONG_MAX || num == LLONG_MIN)) || (errno != 0 && num == 0))
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }

    *result = num;
    return OK;
}

int is_operator(const char symbol)
{
    return ((symbol == '(') || (symbol == ')') || (symbol == '+') ||
            (symbol == '*') || (symbol == '/') || (symbol == '-') ||
            (symbol == '%') || (symbol == '^') || (symbol == '~'));
}

int precedence(char c)
{
    switch (c) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
        case '~':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

enum errors infix_to_postfix(const char *infix, char **postfix)
{
    Stack_char *Stack_char = NULL;
    int idx = 0;

    char c;
    int len = strlen(infix);
    for (int i = 0; i < len; ++i)
    {
        c = infix[i];

        if (isdigit(c))
        {
            (*postfix)[idx++] = c;
            if (i < len - 1 && !isdigit(infix[i + 1]))
                (*postfix)[idx++] = ' ';
            if(infix[i + 1] == '\0')
                (*postfix)[idx++] = ' ';
        }
        else if (c == '(')
        {
            if (i < len - 1 && infix[i + 1] == ')')
                return EMPTY_BRACKET;
            Stack_char_push(&Stack_char, c);
        }
        else if (c == ')')
        {
            while (Stack_char != NULL && Stack_char->value != '(')
            {
                (*postfix)[idx++] = Stack_char->value;
                (*postfix)[idx++] = ' ';
                Stack_char_pop(&Stack_char, &c);
            }

            if (Stack_char != NULL && Stack_char->value == '(')
                Stack_char_pop(&Stack_char, &c);
            else
                return INVALID_BRACKET;
        }
        else if (is_operator(c))
        {
            while (Stack_char != NULL && precedence(c) <= precedence(Stack_char->value))
            {
                (*postfix)[idx++] = Stack_char->value;
                (*postfix)[idx++] = ' ';
                Stack_char_pop(&Stack_char, &c);
            }
            Stack_char_push(&Stack_char, c);
        }
        else
        {
            return INVALID_INPUT;
        }
    }

    while (Stack_char != NULL && Stack_char->value != '(')
    {
        (*postfix)[idx++] = Stack_char->value;
        (*postfix)[idx++] = ' ';
        Stack_char_pop(&Stack_char, &c);
    }

    if (Stack_char != NULL)
    {
        while(Stack_char != NULL)
            Stack_char_pop(&Stack_char, &c);
        return INVALID_BRACKET;
    }

    if (idx > 0 && (*postfix)[idx - 1] == ' ')
        (*postfix)[idx - 1] = '\0';
    else
        (*postfix)[idx] = '\0';

    return OK;
}

enum errors calculation(const char *postfix, long long *result)
{
    Stack_number *st_num = NULL;
    int len = strlen(postfix);
    char *buff = (char *)malloc(sizeof(char) * (len + 1));

    if (buff == NULL)
        return INVALID_MEMORY;

    int idx_buff = 0;
    int is_num = 0;
    long long int num = 0;

    for (int i = 0; i < len; ++i)
    {
        char c = postfix[i];

        if (isdigit(c))
        {
            buff[idx_buff++] = c;
            is_num = 1;
        }
        else if ((c == ' ' || c == '\0') && is_num)
        {
            buff[idx_buff] = '\0';
            convert_str_to_long_long(buff, &num, 10);
            Stack_number_push(&st_num, num);
            idx_buff = 0;
            is_num = 0;
        }
        else if (c == ' ')
        {
            continue;
        }
        else if (is_operator(c))
        {
            long long first_value, second_value;

            // Pop operands from the stack
            if (popStack(&st_num, &first_value) == INVALID_PARAMETER)
            {
                free(buff);
                Stack_number_free(st_num);
                return UNUSED_DIGITS_OR_OPERATORS;
            }

            if (c == '~')
            {
                num = -first_value;
            }
            else
            {
                if (popStack(&st_num, &second_value) == INVALID_PARAMETER)
                {
                    free(buff);
                    Stack_number_free(st_num);
                    return UNUSED_DIGITS_OR_OPERATORS;
                }

                switch (c)
                {
                    case '+':
                        num = second_value + first_value;
                        break;
                    case '-':
                        num = second_value - first_value;
                        break;
                    case '*':
                        num = second_value * first_value;
                        break;
                    case '/':
                        if (first_value == 0)
                        {
                            free(buff);
                            Stack_number_free(st_num);
                            return DIVIDE_BY_ZERO;
                        }
                        num = second_value / first_value;
                        break;
                    case '%':
                        if (first_value == 0)
                        {
                            free(buff);
                            Stack_number_free(st_num);
                            return DIVIDE_BY_ZERO;
                        }
                        if (first_value < 0 || second_value < 0)
                        {
                            free(buff);
                            Stack_number_free(st_num);
                            return NEGATIVE_MOD;
                        }
                        num = second_value % first_value;
                        break;
                    case '^':
                        if (first_value < 0)
                        {
                            free(buff);
                            Stack_number_free(st_num);
                            return NEGATIVE_POWER;
                        }
                        if (first_value == 0 && second_value == 0)
                        {
                            free(buff);
                            Stack_number_free(st_num);
                            return NEGATIVE_POWER;
                        }
                        num = binary_pow(second_value, first_value);
                        break;
                    default:
                        free(buff);
                        Stack_number_free(st_num);
                        return INVALID_PARAMETER;
                }
            }
            if (Stack_number_push(&st_num, num) == INVALID_MEMORY)
            {
                free(buff);
                Stack_number_free(st_num);
                return INVALID_MEMORY;
            }
        }
    }

    if (popStack(&st_num, result) == INVALID_PARAMETER)
    {
        free(buff);
        Stack_number_free(st_num);
        return UNUSED_DIGITS_OR_OPERATORS;
    }

    Stack_number_free(st_num);
    free(buff);

    return OK;
}

enum errors creating_error_file(const char * filename, char ** file_error)
{
    char * prefix = "err_";
    *file_error = (char *)malloc(sizeof(char) * (strlen(filename) + strlen(prefix) + 1));

    if (*file_error == NULL)
        return INVALID_MEMORY;

    (*file_error)[0] = '\0';
    strcat(*file_error, prefix);
    strcat(*file_error, filename);
    return OK;
}

enum errors read_string(FILE * input, char ** infix, int * capacity_infix)
{
    int idx = 0;
    char c = fgetc(input);

    if(c == '\n' || c == EOF)
    {
        (*infix)[idx] = '\0';
        return EMPTY_LINE;
    }

    while(c != '\n' && c != EOF)
    {
        if(idx + 1 >= *capacity_infix)
        {
            (*capacity_infix) *= 2;
            char * for_realloc = (char *) realloc(*infix, *capacity_infix);
            if(for_realloc == NULL) return INVALID_MEMORY;
            *infix = for_realloc;
        }
        (*infix)[idx++] = c;
        c = fgetc(input);
    }

    (*infix)[idx] = '\0';

    return OK;
}

void print_error(FILE * output, enum errors err, int count_line)
{
    switch (err)
    {
        case EMPTY_LINE:
            fprintf(output, "№%d: empty line\n", count_line);
            break;
        case EMPTY_BRACKET:
            fprintf(output, "№%d: empty bracket\n", count_line);
            break;
        case INVALID_INPUT:
            fprintf(output, "№%d: invalid operand\n", count_line);
            break;
        case INVALID_BRACKET:
            fprintf(output, "№%d: invalid bracket\n", count_line);
            break;
        default:
            fprintf(output, "№%d: ????\n", count_line);
            break;
    }
}

int main(int argc, char * argv[])
{
    if(argc == 1)
    {
        printf("Usage: %s file1.txt file2.txt ...\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * input = NULL;
    FILE * err_output = NULL;

    int capacity_infix = SIZE;
    char * infix = (char *) malloc(sizeof(char) * capacity_infix);
    if(infix == NULL)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
    }

    char * err_filename = NULL;

    int count_line = 0;
    enum errors err = OK;
    for (int i = 1; i < argc; ++i)
    {
        input = fopen(argv[i], "r");
        if(input == NULL)
        {
            printf("Error opening file %s\n", argv[i]);
            continue;
        }

        printf("file: %s\n", argv[i]);

        if(creating_error_file(argv[i], &err_filename) == INVALID_MEMORY)
        {
            printf("memory allocation error\n");
            free(infix);
            fclose(input);
            return INVALID_MEMORY;
        }

        while (!feof(input))
        {
            err = read_string(input, &infix, &capacity_infix);
            if(err == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(input);
                free(infix);
                free(err_filename);
                return INVALID_MEMORY;
            }
            else if(err != OK)
            {
                if (err_output == NULL)
                {
                    err_output = fopen(err_filename, "w");
                    if(err_output == NULL)
                    {
                        printf("Error opening file %s\n", err_filename);
                        fclose(input);
                        free(infix);
                        free(err_filename);
                        return ERROR_OPEN_FILE;
                    }
                }
                print_error(err_output, err, count_line);
                ++count_line;
                free(err_filename);
                continue;
            }

            char * postfix = (char *) malloc(sizeof(char) * ( 3 * strlen(infix) + 1));
            if(postfix == NULL)
            {
                fclose(input);
                free(infix);
                free(err_filename);
                return INVALID_MEMORY;
            }

            err = infix_to_postfix(infix, &postfix);
            if(err != OK)
            {
                if (err_output == NULL)
                {
                    err_output = fopen(err_filename, "w");
                    if(err_output == NULL)
                    {
                        printf("Error opening file %s\n", err_filename);
                        fclose(input);
                        free(infix);
                        free(postfix);
                        free(err_filename);
                        return ERROR_OPEN_FILE;
                    }
                }
                print_error(err_output, err, count_line);
                ++count_line;
                free(postfix);
                continue;
            }

            //вычислем значение

            printf("№%d '%s' | '%s'\n", count_line, infix, postfix);
            count_line++;

            free(postfix);
        }

        if(err_output != NULL)
        {
            printf("Errors were found when calculating the expression;\n"
                   "They are located in this file: %s\n", err_filename);
            fclose(err_output);
            err_output = NULL;
        }

        count_line = 0;
        fclose(input);
        free(err_filename);
    }

    free(infix);
    return 0;
}