#include <stdio.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

void print_tree(FILE * input, FILE * output)
{
    char c = fgetc(input);
    if(c == '\n' || c == EOF)
        fprintf(output, "\\_\n");

    int count = 0;
    while (c != '\n' && c != EOF)
    {
        if(c == '(')
        {
            count++;
        }
        else if(c == ')')
        {
            count--;
        }
        else if (c == ' ' || c == ',')
        {
            c = fgetc(input);
            continue;
        }
        else
        {
            for(int i = 0; i < count * 3; ++i)
            {
                fprintf(output, " ");
            }
            fprintf(output, "\\_%c\n", c);
        }
        c = fgetc(input);
    }
}


int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * input = fopen(argv[1], "r");
    FILE * output = fopen(argv[2], "w");
    if(input == NULL || output == NULL)
    {
        printf("Error opening files\n");
        if(!input) fclose(input);
        if(!output) fclose(output);
        return ERROR_OPEN_FILE;
    }

    int count = 1;
    while (!feof(input))
    {
        fprintf(output, "tree №%d\n", count);
        print_tree(input, output);
        fprintf(output, "\n");
        count++;
    }

    printf("construction of trees using bracket expression is completed\n");


    fclose(input);
    fclose(output);
    return 0;
}