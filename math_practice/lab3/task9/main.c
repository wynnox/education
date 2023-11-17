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

Node * search_node(Node * root, char * word)
{
    if (root == NULL)
    {
        return NULL;
    }

    if(strcmp(word, root->word) < 0)
    {
        root->left = search_node(root->left, word);
    }
    else if (strcmp(word, root->word) > 0)
    {
        root->right = search_node(root->right, word);
    }
    else
    {
        return root;
    }

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
    // TODO: убрать костыль
    char for_sep[2] = " ";
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

void menu()
{
    printf("\n"
           "0. call menu\n"
           "1. Counting the number of occurrences of a word\n"
           "2. Displaying the most frequently occurring words\n"
           "3. Finding the longest and shortest word\n"
           "4. Finding the depth of a given tree\n"
           "5. Saving a tree to a file and restoring it\n"
           "6. Exit\n"
           );
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
        if(strlen(argv[i]) != 1)
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

    menu();
    printf("Select option: ");
    int flag_stop = 0;
    char choice;
    while (!flag_stop)
    {
        if(scanf(" %c", &choice) == EOF)
        {
            break;
        }

        //TODO: какая же залупа, почитать ещё
        while (getchar() != '\n');
        switch (choice)
        {
            case '0':
                menu();
                break;
            case '1':
                // TODO: поменять на динамику со статики
                char buff[21];
                printf("Enter a search word (limit 20 characters): ");
                scanf("%20s", buff);
                //TODO: какая же залупа, почитать ещё
                while (getchar() != '\n');

                Node * search = search_node(root, buff);
                if(search == NULL)
                {
                    printf("number of words '%s' found in the text: %d\n", buff, 0);
                }
                else
                {
                    printf("number of words '%s' found in the text: %d\n", search->word, search->count);
                }
                break;
            case '2':

                // TODO: вывод первых n наиболее часто встречающихся слов в файле (значение n вводится с консоли)

                break;
            case '3':

                // TODO: Поиск и вывод в контексте вызывающего кода в консоль самого длинного и самого короткого слова (если таковых несколько,необходимо вывести в консоль любое из них)

                break;
            case '4':

                // TODO: поиска глубины данного дерева

                break;
            case '5':

                // TODO: кинуть дерево в файл а потом обратно воссоздать такое же

                break;
            case '6':
                flag_stop = 1;
                break;
            default:
//                printf("select a number from the menu\n");
//                menu();
                break;
        }
        if(!flag_stop) printf("Select option: ");
    }

    fclose(filename);
    free(separator);
    delete_tree(root);

    return 0;
}