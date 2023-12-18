#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

        int check = (*array)[*size].id;

        for(int i = 0; i < (*size); ++i)
        {
            if((*array)[i].id == check) return INVALID_INPUT;
        }

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
    if (fabs(emp_b->average_score - emp_a->average_score) < EPSILON)
    {
        return 0;
    }
    else if (emp_b->average_score > emp_a->average_score)
    {
        return 1;
    }
    return -1;
}

void menu()
{
    printf("Menu:\n"
           "line limit - 50 characters\n"
           "1. Search by id\n"
           "2. Search by first name\n"
           "3. Search by last name\n"
           "4. Search by group\n"
           "5. outputting student information to a file (id) (filename from command line)\n"
           "6. output to a file information about a student whose average score is higher than the rest(filename from command line arguments)\n"
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
        printf("error input\n");
        fclose(input);
        free(input_array);
        return INVALID_INPUT;
    }

    fclose(input);

    print_array(input_array, size);

    menu();

    char choice;
    int flag = 1;
    while (flag)
    {
        printf("your choice:");
        char c;
        int err = scanf("%c%c", &choice, &c);
        if(c != '\n') while ((c = getchar()) != '\n' && c != EOF);
        if(err == EOF)
        {
            flag = 0;
            continue;
        }
        if(err != 2)
        {
            continue;
        }
        switch (choice)
        {
            case '1':
                qsort(input_array, size, sizeof(Student), compare_id);
                printf("array sorted by id\n");
                print_array(input_array, size);
                break;
            case '2':
                qsort(input_array, size, sizeof(Student), compare_name);
                printf("array sorted by name\n");
                print_array(input_array, size);
                break;
            case '3':
                qsort(input_array, size, sizeof(Student), compare_surname);
                printf("array sorted by surname\n");
                print_array(input_array, size);
                break;
            case '4':
                qsort(input_array, size, sizeof(Student), compare_group);
                printf("array sorted by group\n");
                print_array(input_array, size);
                break;
            case '5':
                printf("enter student id: ");
                int search_id;
                int errr = scanf("%d", &search_id);
                while ((c = getchar()) != '\n' && c != EOF);
                if(errr != 1) break;

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
                fprintf(cho, "%d %s %s %s %lf\n", st.id, st.name, st.surname, st.group, st.average_score);

                printf("file entry has been made\n");

                fclose(cho);

                break;
            case '6':
                qsort(input_array, size, sizeof(Student), compare_score);
                print_array(input_array, size);

                char buff[50];
                printf("enter file name: ");
                int err = scanf("%49s", buff);
                while ((c = getchar()) != '\n' && c != EOF);
                if(err != 1)
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
                    fprintf(lol, "%d %s %s %s %c %c %c %c %c\n", st2.id, st2.name, st2.surname, st2.group, st2.marks[0], st2.marks[1], st2.marks[2], st2.marks[3], st2.marks[4]);
                }

                printf("file entry has been made\n");
                fclose(lol);
                break;
            case '7':
                free(input_array);
                return 0;
            default:
                break;
        }
    }

    free(input_array);
    return 0;
}