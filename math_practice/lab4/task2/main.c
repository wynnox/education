#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#define SIZE_CAPACITY 20
#define SIZE_ARRAY 26
#define EPSILON 1e-6

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    EMPTY_ARRAY
};

typedef struct
{
    char name;
    int * data;
    int size;
    int capacity;
} Array;

enum errors read_command(FILE * input, char ** str, int * capacity)
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

void destroy_arrays(Array ** array)
{
    for (int i = 0; i < SIZE_ARRAY; ++i)
    {
        if ((array)[i] != NULL)
        {
            free((array)[i]->data);
            free((array)[i]);
        }
    }
    free(array);
}

enum errors load(FILE * input, Array ** a)
{
    if (*a == NULL)
    {
        (*a) = (Array *)malloc(sizeof(Array));
        (*a)->data = NULL;
        if ((*a) == NULL)
        {
            return INVALID_MEMORY;
        }
    }

    int value;
    int size = 0;
    int capacity = SIZE_CAPACITY;
    int * nums = (int *) malloc(capacity * sizeof(int));
    if(nums == NULL)
    {
        return INVALID_MEMORY;
    }

    while (fscanf(input, "%d", &value) == 1)
    {
        if (size == capacity)
        {
            capacity *= 2;
            int *for_realloc = (int *)realloc(nums, capacity * sizeof(int));
            if (for_realloc == NULL)
                return INVALID_MEMORY;
            nums = for_realloc;
        }
        nums[size++] = value;
    }

    if(!feof(input)) return INVALID_INPUT;

    if((*a)->data != NULL)
        free((*a)->data);

    (*a)->data = nums;
    (*a)->capacity = capacity;
    (*a)->size = size;

    return OK;
}

enum errors save(FILE * output, Array * array)
{
    if(array == NULL) return EMPTY_ARRAY;
    for(int i = 0; i < array->size; ++i)
    {
        fprintf(output, "%d ", array->data[i]);
    }
    fprintf(output, "\n");
    return OK;
}

int compare_a(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int compare_d(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

int compare_s(const void *a, const void *b) {
    return rand() % 3 - 1;
}

int generate_random_number(int lb, int rb)
{
    return rand() % (rb - lb + 1) + lb;
}

enum errors rand_arr(Array **a, char name, int count, int lb, int rb)
{
    if (*a == NULL)
    {
        *a = (Array *)malloc(sizeof(Array));
        (*a)->data = NULL;
        if (*a == NULL)
        {
            return INVALID_MEMORY;
        }
    }

    if(lb > rb)
    {
        int tmp = lb;
        lb = rb;
        rb = tmp;
    }

    int * nums = (int *) malloc(count * sizeof(int));
    if(nums == NULL)
    {
        return INVALID_MEMORY;
    }

    int idx = 0;
    for(int i = 0; i < count; ++i)
    {
        nums[idx++] = lb + rand() % (rb - lb + 1);
    }

    if((*a)->data != NULL)
        free((*a)->data);
    (*a)->data = nums;
    (*a)->capacity = count;
    (*a)->size = idx;

    return OK;
}

enum errors concat(Array **a, Array ** b)
{
    if (*a == NULL || *b == NULL)
    {
        return EMPTY_ARRAY;
    }

    int len = (*a)->size + (*b)->size;
    int * nums = (int *) malloc(len * sizeof(int));
    if(nums == NULL)
    {
        return INVALID_MEMORY;
    }

    int idx = 0;
    for(int i = 0; i < (*a)->size; ++i)
    {
        nums[idx++] = (*a)->data[i];
    }

    for (int j = 0; j < (*b)->size; ++j)
    {
        nums[idx++] = (*b)->data[j];
    }

    free((*a)->data);

    (*a)->data = nums;
    (*a)->capacity = len;
    (*a)->size = idx;

    return OK;
}

enum errors remove_arr(Array **a, int lb, int count)
{
    if (*a == NULL)
    {
        return EMPTY_ARRAY;
    }

    int * nums = (int *) malloc((*a)->size * sizeof(int));
    if(nums == NULL)
    {
        return INVALID_MEMORY;
    }

    int idx = 0;
    int rb = lb + count - 1;
    for(int i = 0; i < (*a)->size; ++i)
    {
        if(i >= lb && i <= rb) continue;
        nums[idx++] = (*a)->data[i];
    }

    free((*a)->data);

    (*a)->data = nums;
    (*a)->capacity = (*a)->size;
    (*a)->size = idx;

    return OK;
}

enum errors copy_arr(Array **a, int lb, int rb, Array ** b)
{
    if (*a == NULL || *b == NULL)
    {
        return EMPTY_ARRAY;
    }

    int * nums = (int *) malloc((*a)->size * sizeof(int));
    if(nums == NULL)
    {
        return INVALID_MEMORY;
    }

    if(lb > rb)
    {
        int tmp = lb;
        lb = rb;
        rb = tmp;
    }

    int idx = 0;
    for(int i = 0; i < (*a)->size; ++i)
    {
        if(i >= lb && i <= rb)
        {
            nums[idx++] = (*a)->data[i];
        }
    }

    free((*b)->data);

    (*b)->data = nums;
    (*b)->capacity = (*a)->size;
    (*b)->size = idx;

    return OK;
}

void print_all(Array *a)
{
    for(int i = 0; i < (a)->size; ++i)
    {
        printf("%d ", (a)->data[i]);
    }
    printf("\n");
}

void print_b(Array * a, int lb, int rb)
{
    if(lb > rb)
    {
        int tmp = lb;
        lb = rb;
        rb = tmp;
    }

    for(int i = 0; i < (a)->size; ++i)
    {
        if(i >= lb && i <= rb)
        {
            printf("%d ", (a)->data[i]);
        }
    }
    printf("\n");
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * death_note = fopen(argv[1], "r");
    if(death_note == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    int capacity_command = SIZE_CAPACITY;
    char * command = (char *) malloc(capacity_command * sizeof(char));
    if(command == NULL)
    {
        printf("memory allocation error\n");
        fclose(death_note);
        return INVALID_MEMORY;
    }

    char buffer[50];

    Array ** array = (Array **)calloc(sizeof(Array *), SIZE_ARRAY);
    if(array == NULL)
    {
        printf("memory allocation error\n");
        fclose(death_note);
        free(command);
        return INVALID_MEMORY;
    }

    srand(time(NULL));

    enum errors err = OK;
    int count_line = 0;
    while (!feof(death_note))
    {
        err = read_command(death_note, &command, &capacity_command);
        count_line++;

#ifdef DEBUG
        printf("-->№%d %s\n", count_line, command);
#endif

        if(err != OK)
        {
            printf("memory allocation error\n");
            fclose(death_note);
            free(command);
            destroy_arrays(array);
            return INVALID_MEMORY;
        }

        if(strstr(command, "Load"))
        {
            char array_name;
            sscanf(command, "Load %c, %49s", &array_name, buffer);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            FILE * in = fopen(buffer, "r");
            if(in == NULL)
            {
                printf("Error opening file %s\n", buffer);
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return ERROR_OPEN_FILE;
            }

            err = load(in, &arr);

            if(err != OK)
            {
                if(err == INVALID_INPUT)
                    printf("error\n");
                else
                    printf("memory allocation error\n");
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                fclose(in);
                return INVALID_MEMORY;
            }

            fclose(in);

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif
            array[idx] = arr;
        }
        else if(strstr(command, "Save"))
        {
            char array_name;
            sscanf(command, "Save %c, %49s", &array_name, buffer);

            array_name = toupper(array_name);

            FILE * out = fopen(buffer, "a");
            if(out == NULL)
            {
                printf("Error opening file %s\n", buffer);
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return ERROR_OPEN_FILE;
            }

            err = save(out, array[array_name - 'A']);

            if(err == EMPTY_ARRAY)
            {
                printf("error: №%d '%s' (empty array)\n",count_line, command);
                fclose(out);
                continue;
            }

            fclose(out);
        }
        else if(strstr(command, "Rand"))
        {
            char array_name;
            int count, lb, rb;
            sscanf(command, "Rand %c, %d, %d, %d", &array_name, &count, &lb, &rb);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            err = rand_arr(&arr, array_name, count, lb, rb);
            if(err != OK)
            {
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return INVALID_MEMORY;
            }

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif

            array[idx] = arr;
        }
        else if(strstr(command, "Concat"))
        {
            char array_nameA, array_nameB;
            sscanf(command, "Concat %c, %c", &array_nameA, &array_nameB);

            array_nameA = toupper(array_nameA);
            array_nameB = toupper(array_nameB);

            int idxA = array_nameA - 'A';
            Array * arrA = array[idxA];
            int idxB = array_nameB - 'A';
            Array * arrB = array[idxB];

            err = concat(&arrA, &arrB);

            if(err == EMPTY_ARRAY)
            {
                printf("error: №%d '%s' (empty array)\n",count_line, command);
                continue;
            }
            else if(err == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return INVALID_MEMORY;
            }

#ifdef DEBUG
            if(arrA != NULL)
            {
                for(int i = 0; i < arrA->size; ++i)
                {
                    printf("%d ", arrA->data[i]);
                }
                printf("\n");
            }

            if(arrB != NULL)
            {
                for(int i = 0; i < arrB->size; ++i)
                {
                    printf("%d ", arrB->data[i]);
                }
                printf("\n");
            }
#endif
            array[idxA] = arrA;
        }
        else if(strstr(command, "Free"))
        {
            char array_name;
            sscanf(command, "Free(%c)", &array_name);
            array_name = toupper(array_name);

            array[array_name - 'A']->size = 0;
        }
        else if(strstr(command, "Remove"))
        {
            char array_name;
            int lb, count;
            sscanf(command, "Remove %c, %d, %d", &array_name, &lb, &count);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            err = remove_arr(&arr, lb, count);

            if(err == EMPTY_ARRAY)
            {
                printf("error: №%d '%s' (empty array)\n",count_line, command);
                continue;
            }
            else if(err == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return INVALID_MEMORY;
            }

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n%d\n", arr->size);
#endif
            array[idx] = arr;

        }
        else if(strstr(command, "Copy"))
        {
            char array_nameA, array_nameB;
            int lb, rb;
            sscanf(command, "Copy %c, %d, %d, %c", &array_nameA, &lb, &rb,  &array_nameB);

            array_nameA = toupper(array_nameA);
            array_nameB = toupper(array_nameB);

            int idxA = array_nameA - 'A';
            Array * arrA = array[idxA];
            int idxB = array_nameB - 'A';
            Array * arrB = array[idxB];

            err = copy_arr(&arrA, lb, rb, &arrB);

            if(err == EMPTY_ARRAY)
            {
                printf("error: №%d '%s' (empty array)\n",count_line, command);
                continue;
            }
            else if(err == INVALID_MEMORY)
            {
                printf("memory allocation error\n");
                fclose(death_note);
                free(command);
                destroy_arrays(array);
                return INVALID_MEMORY;
            }

#ifdef DEBUG
            if(arrA != NULL)
            {
                for(int i = 0; i < arrA->size; ++i)
                {
                    printf("%d ", arrA->data[i]);
                }
                printf("\n");
            }

            if(arrB != NULL)
            {
                for(int i = 0; i < arrB->size; ++i)
                {
                    printf("%d ", arrB->data[i]);
                }
                printf("\n");
            }
#endif
            array[idxA] = arrA;
        }
        else if(strstr(command, "Sort"))
        {
            char array_name;
            char flag;
            sscanf(command, "Sort %c%c", &array_name, &flag);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            if(arr == NULL)
            {
                printf("error: №%d '%s' (empty array)\n", count_line, command);
                continue;
            }

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif

            if (flag == '+')
                qsort(arr->data, arr->size, sizeof(int), compare_a);
            else
                qsort(arr->data, arr->size, sizeof(int), compare_d);

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif
        }
        else if(strstr(command, "Shuffle"))
        {
            char array_name;
            sscanf(command, "Shuffle %c", &array_name);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            if(arr == NULL)
            {
                printf("error: №%d '%s' (empty array)\n", count_line, command);
                continue;
            }

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif

            qsort(arr->data, arr->size, sizeof(int), compare_s);

#ifdef DEBUG
            for(int i = 0; i < arr->size; ++i)
            {
                printf("%d ", arr->data[i]);
            }
            printf("\n");
#endif
        }
        else if(strstr(command, "Stats"))
        {
            char array_name;
            sscanf(command, "Stats %c", &array_name);

            array_name = toupper(array_name);

            int idx = array_name - 'A';
            Array * arr = array[idx];

            if(arr == NULL)
            {
                printf("error: №%d '%s' (empty array)\n", count_line, command);
                continue;
            }

            int len = arr->size;
            int max = 0, min = INT_MAX;
            int max_i, min_i;
            double average = 0;
            for(int i = 0; i < len; ++i)
            {
                int value = arr->data[i];
                if(value > max)
                {
                    max = value;
                    max_i = i;
                }
                if(value < min)
                {
                    min = value;
                    min_i = i;
                }
                average += value;
            }

            average /= len;

            int *counts = calloc(len, sizeof(int));
            if(counts == NULL)
            {
                printf("memory allocation error\n");
                return INVALID_MEMORY;
            }

            int max_count = 0, k = arr->data[0];
            for(int i = 0; i < len; ++i)
            {
                counts[arr->data[i]]++;
                if(counts[arr->data[i]] > max_count ||
                   (counts[arr->data[i]] == max_count && arr->data[i] > k))
                {
                    max_count = counts[arr->data[i]];
                    k = arr->data[i];
                }
            }

            free(counts);

            printf("size = %d\n", len);
            printf("min = %d (%d), max = %d (%d)\n", min, min_i, max, max_i);
            printf("Most frequent: %d\n", k);
            printf("average = %lf\n", average);
            printf("max deviation = %d\n", abs(max - (int)average) > abs(min - (int)average) ? max : min);

        }
        else if(strstr(command, "Print"))
        {
            char array_name;
            if(strstr(command, "all"))
            {
                sscanf(command, "Print %c, all", &array_name);
                array_name = toupper(array_name);

                int idx = array_name - 'A';
                Array * arr = array[idx];

                if(arr == NULL)
                {
                    printf("error: №%d '%s' (empty array)\n",count_line, command);
                    continue;
                }

                print_all(arr);
            }
            else
            {
                int lb, rb;
                int k = sscanf(command, "Print %c, %d, %d", &array_name, &lb, &rb);
                array_name = toupper(array_name);
                int idx = array_name - 'A';
                Array * arr = array[idx];
                if(arr == NULL)
                {
                    printf("error: №%d '%s' (empty array)\n",count_line, command);
                    continue;
                }

                if(k == 2)
                {
                    if(arr->size > lb && lb >= 0)
                        printf("%d\n", arr->data[lb]);
                    else
                        printf("err\n");
                }
                else if (k == 3)
                {
                    print_b(arr, lb, rb);
                }
            }
        }
        else
        {
            printf("unknown interpreter command\n");
            fclose(death_note);
            free(command);
            destroy_arrays(array);
            return INVALID_INPUT;
        }
    }

    fclose(death_note);
    free(command);
    destroy_arrays(array);

    return 0;
}