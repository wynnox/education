#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct
{
    int id;
    char name[50];
    char surname[50];
    double salary;
} Employee;

#define EPSILON 1e-10

enum errors check_valid(char *str, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return INVALID_INPUT;
    }
    return OK;
}

enum errors read_from_file(FILE *input, Employee **array, int *size, int *capacity)
{
    *size = 0;
    *array = (Employee *)malloc(*capacity * sizeof(Employee));
    if (*array == NULL)
    {
        return INVALID_MEMORY;
    }
    int check;
    while ((check = fscanf(input, "%d\n%49s\n%49s\n%lf\n", &(*array)[*size].id, (*array)[*size].name, (*array)[*size].surname, &(*array)[*size].salary)) == 4)
    {
        if ((*array)[*size].id < 0)
        {
            return INVALID_INPUT;
        }

        if (check_valid((*array)[*size].name, strlen((*array)[*size].name)) != OK)
        {
//            strcpy((*array)[*size].name, "-");
            return INVALID_INPUT;
        }

        if (check_valid((*array)[*size].surname, strlen((*array)[*size].surname)) != OK)
        {
//            strcpy((*array)[*size].surname, "-");
            return INVALID_INPUT;
        }

        if((*array)[*size].salary < 0)
        {
            printf("4");

            return INVALID_INPUT;
        }

        (*size)++;
        if (*capacity == *size)
        {
            *capacity *= 2;
            Employee *for_realloc = realloc(*array, *capacity * sizeof(Employee));
            if (for_realloc == NULL)
            {
                free(*array);
                return INVALID_MEMORY;
            }
            *array = for_realloc;
        }
    }

    if (check < 4 && check > 0) {
        return INVALID_INPUT;
    }

    return OK;
}


void write_in_file(FILE * output, const Employee * array, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        fprintf(output, "%d\n%s\n%s\n%lf\n", array[i].id, array[i].name, array[i].surname, array[i].salary);
    }
}

int compare_a(const void *a, const void *b)
{
    const Employee *emp_a = (const Employee *)a;
    const Employee *emp_b = (const Employee *)b;

    if (emp_a->salary - emp_b->salary > EPSILON)
    {
        return 1;
    }
    if (emp_b->salary - emp_a->salary > EPSILON)
    {
        return -1;
    }

    int sur = strcmp(emp_a->surname, emp_b->surname);
    if (sur != 0)
    {
        return sur;
    }
    int nn = strcmp(emp_a->name, emp_b->name);
    if (nn != 0)
    {
        return nn;
    }
    return emp_a->id - emp_b->id;
}

int compare_b(const void *a, const void *b)
{
    const Employee *emp_a = (const Employee *)a;
    const Employee *emp_b = (const Employee *)b;

    if (emp_b->salary - emp_a->salary > EPSILON)
    {
        return 1;
    }
    if (emp_a->salary - emp_b->salary > EPSILON)
    {
        return -1;
    }

    int sur = strcmp(emp_a->surname, emp_b->surname);
    if (sur != 0)
    {
        return sur;
    }
    int nn = strcmp(emp_a->name, emp_b->name);
    if (nn != 0)
    {
        return nn;
    }
    return emp_a->id - emp_b->id;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Invalid number of arguments\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0'))
    {
        printf("incorrect input\n");
        return INVALID_INPUT;
    }

    FILE *input = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");
    if (input == NULL || output == NULL)
    {
        if (!input)
            fclose(input);
        if (!output)
            fclose(output);
        printf("error when opening file\n");
        return ERROR_OPEN_FILE;
    }

    Employee *input_array = NULL;
    int size = 0, capacity_array = 2;
    switch (argv[1][1])
    {
        case 'a':
            if(read_from_file(input, &input_array, &size, &capacity_array) != OK)
            {
                printf("error\n");
                fclose(input);
                fclose(output);
                free(input_array);
                return INVALID_INPUT;
            }
            qsort(input_array, size, sizeof(Employee), compare_a);
            write_in_file(output, input_array, size);
            free(input_array);
            break;
        case 'd':
            if(read_from_file(input, &input_array, &size, &capacity_array) != OK)
            {
                printf("error\n");
                fclose(input);
                fclose(output);
                free(input_array);
                return INVALID_INPUT;
            }
            qsort(input_array, size, sizeof(Employee), compare_b);
            write_in_file(output, input_array, size);
            free(input_array);
            break;
        default:
            printf("incorrect input\n");
            break;
    }
    fclose(input);
    fclose(output);

    return 0;
}
