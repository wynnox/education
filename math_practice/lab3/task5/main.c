#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EPSILON 1e-6

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
    char group[50];
    unsigned char marks[5];
    double average_score;
} Student;

enum errors check_valid(char *str, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return INVALID_INPUT;
    }
    return OK;
}

enum errors read_from_file(FILE *input, Student **array, int *size, int *capacity)
{
    *size = 0;
    *array = (Student *)malloc(*capacity * sizeof(Student));
    if (*array == NULL)
    {
        return INVALID_MEMORY;
    }

    int check;
    while ((check = fscanf(input, "%d %49s %49s %49s %c %c %c %c %c",
                           &(*array)[*size].id, (*array)[*size].name, (*array)[*size].surname,
                           (*array)[*size].group, &(*array)[*size].marks[0], &(*array)[*size].marks[1],
                           &(*array)[*size].marks[2], &(*array)[*size].marks[3],
                           &(*array)[*size].marks[4])) == 9)
    {
        if ((*array)[*size].id < 0)
        {
            return INVALID_INPUT;
        }

        //чекнуть есть ли айдишка уже

        if (check_valid((*array)[*size].name, strlen((*array)[*size].name)) != OK)
        {
            return INVALID_INPUT;
        }

        if (check_valid((*array)[*size].surname, strlen((*array)[*size].surname)) != OK)
        {
            return INVALID_INPUT;
        }

        (*array)[*size].average_score = 0;
        for(int i = 0; i < 5; ++i)
        {
            unsigned char mark = (*array)[*size].marks[i];
            (*array)[*size].average_score += (mark - '0');
            if(!(mark >= '2' && mark <= '5'))
            {
                return INVALID_INPUT;
            }
        }

        (*array)[*size].average_score /= 5;

        (*size)++;
        if (*capacity == *size)
        {
            *capacity *= 2;
            Student *for_realloc = realloc(*array, *capacity * sizeof(Student));
            if (for_realloc == NULL)
            {
                free(*array);
                return INVALID_MEMORY;
            }
            *array = for_realloc;
        }
    }

    if (check < 9 && check > 0)
    {
        return INVALID_INPUT;
    }

    return OK;
}

void print_array(Student *array, int size)
{
    for(int i = 0; i < size; ++i)
    {
        Student st = array[i];
        printf("№%d %s %s %s ", st.id, st.name, st.surname, st.group);
        for(int i = 0; i < 5; ++i)
        {
            unsigned char mark = st.marks[i];
            printf("%c ", mark);
        }
        printf("%lf", st.average_score);
        printf("\n");
    }
}

int compare_id(const void *a, const void *b)
{
    const Student *emp_a = (const Student *)a;
    const Student *emp_b = (const Student *)b;

    return emp_a->id - emp_b->id;
}

int compare_surname(const void *a, const void *b)
{
    const Student *emp_a = (const Student *)a;
    const Student *emp_b = (const Student *)b;

    return strcmp(emp_a->surname,  emp_b->surname);
}

int compare_name(const void *a, const void *b)
{
    const Student *emp_a = (const Student *)a;
    const Student *emp_b = (const Student *)b;

    return strcmp(emp_a->name,  emp_b->name);
}

int compare_group(const void *a, const void *b)
{
    const Student *emp_a = (const Student *)a;
    const Student *emp_b = (const Student *)b;

    return strcmp(emp_a->group,  emp_b->group);
}

int compare_score(const void *a, const void *b)
{
    const Student *emp_a = (const Student *)a;
    const Student *emp_b = (const Student *)b;


    if (emp_b->average_score - emp_a->average_score > EPSILON)
    {
        return 1;
    }
    if (emp_a->average_score - emp_b->average_score > EPSILON)
    {
        return -1;
    }

    return 0;
}

void menu()
{
    printf("Menu:\n"
           "1. Search by id\n"
           "2. Search by first name\n"
           "3. Search by last name\n"
           "4. Search by group\n"
           "5. outputting student information to a file (id)\n"
           "6. output to a file information about a student whose average score is higher than the rest\n"
           "7. Exit\n");
}

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s file.txt\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    Student *input_array = NULL;
    int size = 0, capacity_array = 2;
    if(read_from_file(input, &input_array, &size, &capacity_array) != OK)
    {
        printf("error\n");
        fclose(input);
        free(input_array);
        return INVALID_INPUT;
    }

    fclose(input);

    print_array(input_array, size);

    menu();

    int choice;
    int flag = 1;
    while (flag)
    {
        printf("your choice:");
        int err = scanf("%d", &choice);
        if(err == EOF)
        {
            flag = 0;
            continue;
        }
        if(err != 1) continue;
        switch (choice)
        {
            case 1:
                qsort(input_array, size, sizeof(Student), compare_id);
                printf("array sorted by id\n");
                print_array(input_array, size);
                break;
            case 2:
                qsort(input_array, size, sizeof(Student), compare_name);
                printf("array sorted by name\n");
                print_array(input_array, size);
                break;
            case 3:
                qsort(input_array, size, sizeof(Student), compare_surname);
                printf("array sorted by surname\n");
                print_array(input_array, size);
                break;
            case 4:
                qsort(input_array, size, sizeof(Student), compare_group);
                printf("array sorted by group\n");
                print_array(input_array, size);
                break;
            case 5:
                printf("enter student id: ");
                int search_id;
                if(!scanf("%d", &search_id)) break;

                Student st;
                int i = 0;
                int flag = 0;
                for(; i < size; ++i)
                {
                    st = input_array[i];
                    if(st.id == search_id)
                    {
                        search_id = st.id;
                        flag = 1;
                        break;
                    }
                }

                if(!flag)
                {
                    printf("student not found\n");
                    break;
                }

                FILE * cho = fopen(argv[2], "a");
                if(cho == NULL)
                {
                    printf("Error opening file %s\n", argv[2]);
                    break;
                }

                st = input_array[i];
                fprintf(cho, "%s %s %s %lf\n", st.name, st.surname, st.group, st.average_score);

                printf("file entry has been made\n");

                fclose(cho);

                break;
            case 6:
                qsort(input_array, size, sizeof(Student), compare_score);
                print_array(input_array, size);

                char buff[50];
                printf("enter file name: ");
                if(!scanf("%49s", buff))
                {
                    printf("error\n");
                }

                if(strcmp(argv[1], buff) == 0)
                {
                    printf("this file cannot be used\n");
                    break;
                }

                FILE * lol = fopen(buff, "a");
                if(lol == NULL)
                {
                    printf("Error opening file %s\n", buff);
                    break;
                }

                Student st1 = input_array[0];
                fprintf(lol, "%s %s\n", st1.name, st1.surname);
                for(int i = 1; i < size; ++i)
                {
                    Student st2 = input_array[i];
                    if(st1.average_score - st2.average_score > EPSILON) break;
                    fprintf(lol, "%s %s\n", st2.name, st2.surname);
                }

                printf("file entry has been made\n");
                fclose(lol);
                break;
            case 7:
                free(input_array);
                return 0;
            default:
                break;
        }
    }

    free(input_array);
    return 0;
}