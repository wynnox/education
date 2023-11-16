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

typedef struct Node
{
    char * word;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(char * word)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        return NULL;
    }

    new_node->word = (char *)malloc( (strlen(word) + 1) * sizeof(char));
    if(new_node->word == NULL)
    {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->word, word);

    new_node->count = 1;

    new_node->left = new_node->right = NULL;

    return new_node;
}

Node * insert_node(Node * root, char * word)
{
    if (root == NULL)
    {
        return create_node(word);
    }

    if(strcmp(word, root->word) < 0)
    {
        root->left = insert_node(root->left, word);
    }
    else if (strcmp(word, root->word) > 0)
    {
        root->right = insert_node(root->right, word);
    }
    else
    {
        root->count++;
    }

    return root;
}

enum errors read_from_file(FILE * filename, Node ** root, const char * separator)
{
    int len_buffer = 0, capacity_buffer = 20;
    char * buffer = (char *)malloc(capacity_buffer * sizeof(char));
    if (buffer == NULL)
    {
        return INVALID_MEMORY;
    }
    buffer[0] = '\0';

    char c;
    char for_sep[2] = "\0\0";
    while(!feof(filename))
    {
        c = fgetc(filename);

        if(c == EOF && len_buffer != 0)
        {
            *root = insert_node(*root, buffer);
            if(*root == NULL)
            {
                //что тут?
                return INVALID_MEMORY;
            }
//            printf("%s\n", buffer);
            continue;
        }

        for_sep[0] = c;
        char * token = strstr(separator, for_sep);
        if(token == NULL)
        {
            strcat(buffer, for_sep);
            len_buffer++;
        }
        else if(len_buffer == 0)
        {
            continue;
        }
        else
        {
            *root = insert_node(*root, buffer);
            if(*root == NULL)
            {
                //что тут?
                return INVALID_MEMORY;
            }
//            printf("%s\n", buffer);
            buffer[0] = '\0';
            len_buffer = 0;
        }

        if(len_buffer + 1 == capacity_buffer)
        {
            capacity_buffer *= 2;
            char * for_realloc = (char *)realloc(buffer, capacity_buffer);
            if(for_realloc == NULL)
            {
                free(buffer);
                return INVALID_MEMORY;
            }
            buffer = for_realloc;
        }
    }
//    printf("\n");
    free(buffer);
    return OK;
}

//void inorder(Node* root)
//{
//    if (root == NULL)
//    {
//        return;
//    }
//    inorder(root->left);
//    printf("%s(%d) ", root->word, root->count);
//    inorder(root->right);
//}

void inorder(Node* root, int depth) {
    if (root == NULL)
    {
        return;
    }
    inorder(root->right, depth + 1);
    for (int i = 0; i < depth * 3; i++) {
        printf(" ");
    }
    printf("\\_%s\n", root->word);
    inorder(root->left, depth + 1);
}


Node * delete_tree(Node* root) {
    if (root)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root->word);
        free(root);
    }
    return NULL;
}


int main(int argc, char * argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <filename> <separator1> <separator2> ...\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * filename = fopen(argv[1], "r");
    if(filename == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    int len_separator = argc - 2;
    char * separator = (char *)malloc((len_separator + 1) * sizeof(char));
    if(separator == NULL)
    {
        printf("memory allocation error\n");
        fclose(filename);
        return INVALID_MEMORY;
    }
    separator[0] = '\0';

    for(int i = 2; i < argc; ++i)
    {
        if(strlen(argv[i]) > 1)
        {
            printf("separator must be one character: %s\n", argv[i]);
            fclose(filename);
            free(separator);
            return INVALID_INPUT;
        }
        strcat(separator, argv[i]);
    }
    printf("separator: %s\n", separator);

    Node * root = NULL;
    if(read_from_file(filename, &root, separator) == INVALID_MEMORY)
    {
        printf("memory allocation error\n");
        fclose(filename);
        free(separator);
        root = delete_tree(root);
        return INVALID_MEMORY;
    }

    inorder(root, 0);

    fclose(filename);
    free(separator);
    delete_tree(root);

    return 0;
}
