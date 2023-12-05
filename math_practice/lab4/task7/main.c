#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>


#define SIZE_CAPACITY 20

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    OVERFLOW_ERROR,
    DIVISION_BY_ZERO
};

typedef struct MemoryCell
{
    char * name;
    long int value;
} MemoryCell;

typedef struct Variables
{
    long int capacity;
    long int size;
    MemoryCell ** array;
} Variables;

Variables * create_variables()
{
    Variables * var = (Variables *) malloc(sizeof(Variables));
    if(var == NULL)
    {
        return NULL;
    }

    var->capacity = SIZE_CAPACITY;
    var->size = 0;

    var->array = (MemoryCell **) malloc(sizeof(MemoryCell *) * SIZE_CAPACITY);
    if(var->array == NULL)
    {
        free(var);
        return NULL;
    }

    return var;
}

MemoryCell * create_mc(char * name, long int num)
{
    MemoryCell * var = (MemoryCell *) malloc(sizeof(MemoryCell));
    if(var == NULL)
    {
        return NULL;
    }

    long int len_name = strlen(name);

    var->name = (char *) malloc((len_name + 1) * sizeof(char ));
    if(var->name == NULL)
    {
        free(var);
        return NULL;
    }

    strcpy(var->name, name);
    var->value = num;

    return var;
}

int compare(const void* a, const void* b)
{
    MemoryCell* mc1 = *(MemoryCell**)a;
    MemoryCell* mc2 = *(MemoryCell**)b;
    return strcmp(mc1->name, mc2->name);
}

MemoryCell* search_variable(Variables* vars, char* name)
{
    int left = 0;
    int right = vars->size - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int res = strcmp(vars->array[mid]->name, name);
        if (res == 0)
        {
            return vars->array[mid];
        }
        if (res < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return NULL;
}

enum errors add_variable(Variables* vars, char* name, long int num)
{
    if (vars->size == vars->capacity) {
        vars->capacity *= 2;
        MemoryCell** for_realloc = (MemoryCell**)realloc(vars->array, vars->capacity * sizeof(MemoryCell*));
        if(for_realloc == NULL)
        {
            return INVALID_MEMORY;
        }
        vars->array = for_realloc;
    }
    MemoryCell* new_var = create_mc(name, num);
    if(new_var == NULL)
    {
        return INVALID_MEMORY;
    }
    vars->array[vars->size++] = new_var;
    qsort(vars->array, vars->size, sizeof(MemoryCell*), compare);
    return OK;
}

void destroy_mc(MemoryCell * var)
{
    free(var->name);
    free(var);
}

void destroy_variables(Variables * vars)
{
    for (int i = 0; i < vars->size; ++i)
    {
        destroy_mc(vars->array[i]);
    }
    free(vars->array);
    free(vars);
}

enum errors read_str(FILE * input, char ** str, int * capacity)
{
    char c = fgetc(input);
    int idx = 0;
    while (c != ';')
    {
        (*str)[idx++] = c;
        if (idx == *capacity)
        {
            *capacity *= 2;
            char * for_realloc = (char *)realloc(*str, *capacity);
            if (for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *str = for_realloc;
        }
        c = fgetc(input);
    }
    (*str)[idx] = '\0';
    c = fgetc(input);
    if (c == EOF)
    {
        return OK;
    }
    return OK;
}

enum errors convert_str_to_int (const char *str, long int * result, int base)
{
    char *endptr;
    long num = strtol(str, &endptr, base);

    if (errno == ERANGE && (num == LONG_MAX || num == LONG_MIN))
    {
        return INVALID_INPUT;
    }
    else if (errno != 0 && num == 0)
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

int check_is_digit(char * str)
{
    size_t i = 0;
    for(; i < strlen(str); ++i)
    {
        if(!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

enum errors get_num(MemoryCell * var, long int * num, char * buffer, int * flag_negative)
{
    if(var == NULL)
    {
        enum errors err = convert_str_to_int(buffer, num, 10);
        if(err == INVALID_INPUT)
        {
            if(check_is_digit(buffer))
            {
                return OVERFLOW_ERROR;
            }
            else
            {
                return INVALID_INPUT;
            }
        }
    }
    else
    {
        *num = var->value;
    }

    if(*flag_negative)
    {
        (*num) *= -1;
        *flag_negative = 0;
    }
    return OK;
}

enum errors get_res(char operation, long int num1, long int num2, long int * res)
{
    if(operation == '+')
    {
        if (num1 > 0 && num2 > LONG_MAX - num1) {
            return OVERFLOW_ERROR;
        } else if (num1 < 0 && num2 < LONG_MIN - num1) {
            return OVERFLOW_ERROR;
        }
        *res = num1 + num2;
    }
    else if(operation == '-')
    {
        if (num1 > 0 && num2 < LONG_MIN + num1) {
            return OVERFLOW_ERROR;
        } else if (num1 < 0 && num2 > LONG_MAX + num1) {
            return OVERFLOW_ERROR;
        }
        *res = num1 - num2;
    }
    else if (operation == '*')
    {
        if (num1 > 0 && num2 > LONG_MAX / num1) {
            return OVERFLOW_ERROR;
        } else if (num1 < 0 && num2 < LONG_MIN / num1) {
            return OVERFLOW_ERROR;
        }
        *res = num1 * num2;
    }
    else if(operation == '/')
    {
        if(num2 == 0)
        {
            return DIVISION_BY_ZERO;
        }
        *res = num1 / num2;
    }
    else if(operation == '%')
    {
        if(num2 == 0)
        {
            return DIVISION_BY_ZERO;
        }
        *res = num1 % num2;
    }
    return OK;
}

enum errors execution_instructions(char * str, Variables * vars, const char * operations)
{
    enum errors err;
    int len_str = strlen(str);
    char * buffer = (char *) malloc((len_str + 1) * sizeof(char));
    if(buffer == NULL)
        return INVALID_MEMORY;

    int idx = 0;
    for(;str[idx] != '='; idx++)
    {
        buffer[idx] = str[idx];
    }
    buffer[idx++] = '\0';

    MemoryCell * result = search_variable(vars, buffer);

    int flag_negative = 0;

    if(str[idx] == '~')
    {
        flag_negative = 1;
        idx++;
    }

    int i = 0;
    while (str[idx] != '\0' && strrchr(operations, str[idx]) == NULL)
    {
        buffer[i++] = str[idx++];
    }
    buffer[i] = '\0';

    long int num1;
    MemoryCell * var1 = search_variable(vars, buffer);

    err = get_num(var1, &num1, buffer, &flag_negative);
    if(err != OK)
    {
        free(buffer);
        return err;
    }

    long int res = 0;

    if (str[idx] == '\0')
    {
        res = num1;
    }
    else
    {

        char operation = str[idx++];

        if(str[idx] == '~')
        {
            flag_negative = 1;
            idx++;
        }

        for(i = 0; str[idx] != '\0'; i++, idx++)
        {
            buffer[i] = str[idx];
        }
        buffer[i] = '\0';

        long int num2;
        MemoryCell * var2 = search_variable(vars, buffer);

        err = get_num(var2, &num2, buffer, &flag_negative);
        if(err != OK)
        {
            free(buffer);
            return err;
        }

        err = get_res(operation, num1, num2, &res);
        if(err != OK)
        {
            free(buffer);
            return err;
        }
    }


    if(result == NULL)
    {
        int j = 0;
        for(;str[j] != '='; j++)
        {
            buffer[j] = str[j];
        }
        buffer[j] = '\0';

        enum errors err = add_variable(vars, buffer, res);
        if(err == INVALID_MEMORY)
        {
            free(buffer);
            return INVALID_MEMORY;
        }
    }
    else
    {
        result->value = res;
    }

    free(buffer);
    return OK;
}


void print_all(Variables * vars)
{
    for(int i = 0; i < vars->size; ++i)
    {
        MemoryCell * vvv = vars->array[i];
        printf("%s: %ld\n", vvv->name, vvv->value);
    }
    printf("%ld\n", vars->size);
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * filename = fopen(argv[1], "r");
    if(filename == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    Variables * vars = create_variables();
    if(vars == NULL)
    {
        printf("memory allocation error\n");
        fclose(filename);
        return INVALID_MEMORY;
    }

    int capacity = SIZE_CAPACITY;
    char * buffer = (char *) malloc(capacity * sizeof(char));
    if(buffer == NULL)
    {
        printf("memory allocation error\n");
        fclose(filename);
        destroy_variables(vars);
        return INVALID_MEMORY;
    }


    char operations[6] = "+-*/%";
    while (!feof(filename))
    {
        if(read_str(filename, &buffer, &capacity) != OK)
        {
            printf("memory allocation error\n");
            fclose(filename);
            free(buffer);
            destroy_variables(vars);
            return INVALID_MEMORY;
        }
        if(strcmp("print", buffer) == 0)
        {
            printf("print all\n");
            print_all(vars);
        }
        else if(strstr(buffer, "print") != NULL)
        {
            printf("print var\n");
            char * p = strtok(buffer, " ");
            p = strtok(NULL, " ");
            if(p == NULL)
            {
                printf("unknown variable\n");
                destroy_variables(vars);
                fclose(filename);
                free(buffer);
                return INVALID_INPUT;
            }

            MemoryCell * var = search_variable(vars, p);
            if(var != NULL)
            {
                printf("%s: %ld\n", var->name, var->value);
            }
            else
            {
                printf("unknown variable\n");
                destroy_variables(vars);
                fclose(filename);
                free(buffer);
                return INVALID_INPUT;
            }
        }
        else
        {
            enum errors err=execution_instructions(buffer, vars, operations);
            if(err == INVALID_INPUT)
            {
                printf("unknown variable\n");
                destroy_variables(vars);
                fclose(filename);
                free(buffer);
                return INVALID_INPUT;
            }
            else if(err == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(filename);
                free(buffer);
                destroy_variables(vars);
                return INVALID_MEMORY;
            }
            else if(err == OVERFLOW_ERROR)
            {
                printf("overflow occurred\n");
                fclose(filename);
                free(buffer);
                destroy_variables(vars);
                return OVERFLOW_ERROR;
            }
            else if(err == DIVISION_BY_ZERO)
            {
                printf("division by zero\n");
                fclose(filename);
                free(buffer);
                destroy_variables(vars);
                return DIVISION_BY_ZERO;
            }
        }
    }

    destroy_variables(vars);
    fclose(filename);
    free(buffer);
    return 0;
}