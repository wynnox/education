#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


#define SIZE_CAPACITY 20

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct MemoryCell
{
    char * name;
    int value;
} MemoryCell;

typedef struct Variables
{
    int capacity;
    int size;
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

MemoryCell * create_mc(char * name, int num)
{
    MemoryCell * var = (MemoryCell *) malloc(sizeof(MemoryCell));
    if(var == NULL)
    {
        return NULL;
    }

    int len_name = strlen(name);

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

enum errors add_variable(Variables* vars, char* name, int num)
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
        if(idx == *capacity)
        {
            *capacity *= 2;
            char * for_realloc = (char *) realloc(*str, *capacity);
            if(for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *str = for_realloc;
        }
        c = fgetc(input);
    }
    (*str)[idx] = '\0';
    c = fgetc(input);
    return OK;
}

enum errors convert_str_to_int (const char *str, int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == INT_MAX || *result == INT_MIN))
    {
        return INVALID_INPUT;
    }
    else if (errno != 0 && *result == 0)
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }

    return OK;
}

enum errors execution_instructions(char * str, Variables * vars, const char * operations)
{
    char * op = strpbrk(str, operations);
    char operation;
    if(op != NULL)
    {
        printf("%c\n", *op);
        operation = *op;
    }

    //добавили или нашли переменную
    char * p = strtok(str, "=");
    MemoryCell * result = search_variable(vars, p);
    if(result == NULL)
    {
        add_variable(vars, p, 1);
        result = search_variable(vars, p);
        printf("->%s\n", result->name);
    }
    else
    {
        printf("-->%s\n", result->name);
    }

    if(op != NULL)
    {
        int num1, num2;
        p = strtok(NULL, operations);
        MemoryCell * var1 = search_variable(vars, p);
        if(var1 == NULL)
        {
            // либо число либо переменная которой ещё нет
            convert_str_to_int(p, &num1, 10);
//            printf("%d", num1);
        }
        else
        {
            num1 = var1->value;
        }
//        printf("!%s", var1->name);

        p = strtok(NULL, operations);
        MemoryCell * var2 = search_variable(vars, p);
        if(var2 == NULL)
        {
            convert_str_to_int(p, &num2, 10);
//            printf("%d", num2);
        }
        else
        {
            num2 = var2->value;
        }
        printf("num1 = %d num2 = %d\n", num1, num2);

        if(operation == '+')
        {
            result->value = num1 + num2;
            printf("%s = %d\n", result->name, result->value);
        }
        else if (operation == '*')
        {
            result->value = num1 * num2;
            printf("%s = %d\n", result->name, result->value);

        }
//        else
//        {
//            printf("pupupu\n");
//        }
//            printf("!%s", var2->name);
    }
    else
    {
        int num;
        p = strtok(NULL, operations);
        MemoryCell * var = search_variable(vars, p);

        if(var == NULL)
        {
            convert_str_to_int(p, &num, 10);
            result->value = num;
            printf("%s = %d\n", result->name, result->value);
        }
        else
        {
            result->value = var->value;
            printf("pupupupu\n");
            printf("%s = %d\n", result->name, result->value);
        }
    }

    return OK;
}

void print_all(Variables * vars)
{
    for(int i = 0; i < vars->size; ++i)
    {
        MemoryCell * vvv = vars->array[i];
        printf("%s: %d\n", vvv->name, vvv->value);
    }
    printf("%d", vars->size);
}
//
//void print_var() {}

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
//        printf("%s\n", buffer);
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
            printf("%s\n", p);
            MemoryCell * var = search_variable(vars, p);
            if(var != NULL)
            {
                printf("%s: %d\n", var->name, var->value);
            }
            else
            {
                ////
            }

        }
        else
        {
            execution_instructions(buffer, vars, operations);
        }


    }

    destroy_variables(vars);
    fclose(filename);
    free(buffer);
    return 0;
}
