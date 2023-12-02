#include <stdio.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct Node
{
    char data;
    struct Node* son;
    struct Node* brother;
} Node;

Node * create_node(char data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->son = NULL;
    new_node->brother = NULL;
    return new_node;
}

//void print_tree(FILE* output, Node* root, int depth)
//{
//    if (root == NULL)
//        return;
//
//    print_tree(output, root->brother, depth);
//
//    for (int i = 0; i < depth * 3; i++)
//        fprintf(output, " ");
//
//    fprintf(output, "\\_%c\n", root->data);
//
//    print_tree(output, root->son, depth + 1);
//}

void print_tree(FILE *output, Node *root, int depth)
{
    if (root == NULL)
        return;

    for (int i = 0; i < depth * 3; i++)
        fprintf(output, " ");

    fprintf(output, "\\_%c\n", root->data);

    print_tree(output, root->son, depth + 1);
    print_tree(output, root->brother, depth);
}

//enum errors build_tree(FILE * input, Node ** root)
//{
//    char c = fgetc(input);
//    if(c == EOF || c == '\n') return OK;
//
//    int status;
//
//    if(c == ' ') c = fgetc(input);
//
//    if(c == '(')
//    {
//        c = fgetc(input);
//
//        *root = create_node(c);
//        printf("(%c\n", c);
//        if(*root == NULL)
//        {
//            return INVALID_MEMORY;
//        }
//
//        status = build_tree(input, &((*root)->son));
//        if(status != OK)
//        {
//            return status;
//        }
//
//    }
//    else if (c == ',')
//    {
//        c = fgetc(input);
//        c = fgetc(input);
//
//        *root = create_node(c);
//        printf(",%c\n", c);
//        if (*root == NULL)
//        {
//            return INVALID_MEMORY;
//        }
//
//        status = build_tree(input, &((*root)->brother));
//        if (status != OK)
//        {
//            return status;
//        }
//    }
//    else if(c == ')')
//    {
//        return OK;
//    }
//    else
//    {
//        *root = create_node(c);
//        printf("!%c\n", c);
//        if (*root == NULL)
//        {
//            return INVALID_MEMORY;
//        }
//
//        status = build_tree(input, &((*root)->son));
//        if(status != OK)
//        {
//            return status;
//        }
//    }
//    return OK;
//}

enum errors build_tree(FILE * input, Node ** root)
{
    int status;
    char c = fgetc(input);
    if(c == EOF || c == '\n') return OK;

    *root = create_node(c);
    if (*root == NULL)
    {
        return INVALID_MEMORY;
    }

    c = fgetc(input);

    if(c == '(')
    {
        status = build_tree(input, &((*root)->son));
        if(status != OK)
        {
            return status;
        }
    }
//    else if (c == ',')
//    {
//        fgetc(input);
//        status = build_tree(input, &((*root)->brother));
//        if(status != OK)
//        {
//            return status;
//        }
//        printf("(%c\n", c);
//    }
    else if(c == ')')
    {
        return OK;
    }
    else
    {
        c = fgetc(input);
        if(c == ',')
        {
            status = build_tree(input, &((*root)->brother));
        }
        else
        {
            status = build_tree(input, &((*root)->son));
        }
        if(status != OK)
        {
            return status;
        }
    }
    return OK;
}


void free_tree(Node *root)
{
    if (root == NULL) {
        return;
    }

    free_tree(root->son);
    free_tree(root->brother);

    free(root);
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

    int size_forest = 0, capacity_forest = 20;
    Node** forest = (Node **) malloc(capacity_forest * sizeof(Node*));
    if(forest == NULL)
    {
        printf("memory allocation error\n");
        fclose(input);
        fclose(output);
        return INVALID_MEMORY;
    }

    int status;
    while (!feof(input))
    {
        Node *tree_root = NULL;

        status = build_tree(input, &tree_root);

        if (status != OK)
        {
            printf("memory allocation error\n");
            for (int i = 0; i < size_forest; i++)
            {
                free_tree(forest[i]);
            }
            free(forest);
            fclose(input);
            fclose(output);
            return INVALID_MEMORY;
        }

        if (tree_root != NULL)
        {
            forest[size_forest] = tree_root;
            ++size_forest;

            if (capacity_forest == size_forest)
            {
                capacity_forest *= 2;
                Node **for_realloc = (Node **)realloc(forest, capacity_forest * sizeof(Node *));
                if (for_realloc == NULL)
                {
                    printf("memory allocation error\n");
                    for (int i = 0; i < size_forest; i++)
                    {
                        free_tree(forest[i]);
                    }
                    free(forest);
                    fclose(input);
                    fclose(output);
                    return INVALID_MEMORY;
                }
                forest = for_realloc;
            }
        }
    }

    for (int i = 0; i < size_forest; i++)
    {
        print_tree(output, forest[i], 0);
        fprintf(output, "\n");
    }

    printf("Writing to the file was successful!\n");
    printf("%d\n", size_forest);

    for (int i = 0; i < size_forest; i++)
    {
        free_tree(forest[i]);
    }
    free(forest);

    fclose(input);
    fclose(output);
    return 0;
}