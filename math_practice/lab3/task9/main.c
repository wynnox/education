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
        return search_node(root->left, word);
    }
    else if (strcmp(word, root->word) > 0)
    {
        return search_node(root->right, word);
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
    char for_sep[2] = " ";
    while(!feof(filename))
    {
        c = fgetc(filename);

        if(c == EOF && len_buffer != 0)
        {
            *root = insert_node(*root, buffer);
            if(*root == NULL)
            {
                free(buffer);
                return INVALID_MEMORY;
            }
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
                free(buffer);
                return INVALID_MEMORY;
            }
            buffer[0] = '\0';
            len_buffer = 0;
        }

        if(len_buffer + 1 == capacity_buffer)
        {
            capacity_buffer *= 2;
            char * for_realloc = (char *)realloc(buffer, capacity_buffer * sizeof(Node*));
            if(for_realloc == NULL)
            {
                free(buffer);
                return INVALID_MEMORY;
            }
            buffer = for_realloc;
        }
    }
    free(buffer);
    return OK;
}

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

void preorder(FILE * file, Node* root, char * sep)
{
    if (root == NULL) {
        return;
    }

    fprintf(file, "%s%c", root->word, sep[0]);
    preorder(file, root->left, sep);
    preorder(file, root->right, sep);
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

int max_depth(Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lDepth = max_depth(node->left);
        int rDepth = max_depth(node->right);

        // использовать максимальную из двух глубин
        if (lDepth > rDepth)
            return(lDepth + 1);
        else
            return(rDepth + 1);
    }
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

void search_max_min_word(Node * root, Node ** min, Node ** max)
{
    if(root == NULL)
    {
        return;
    }
    search_max_min_word(root->right, min, max);
    if(strlen(root->word) > strlen((*max)->word))
    {
        *max = root;
    }
    if(strlen(root->word) < strlen((*min)->word))
    {
        *min = root;
    }
    search_max_min_word(root->left, min, max);
}

void collect_nodes(Node* node, Node*** nodes, int* len, int* capacity)
{
    if (node == NULL)
    {
        return;
    }

    collect_nodes(node->left, nodes, len, capacity);

    if (*len == *capacity)
    {
        *capacity *= 2;
        Node** for_realloc = (Node **)realloc(*nodes, *capacity * sizeof(Node*));
        if (for_realloc == NULL)
        {
            printf("Error reallocating memory\n");
            return;
        }
        *nodes = for_realloc;
    }

    (*nodes)[*len] = node;
    (*len)++;

    collect_nodes(node->right, nodes, len, capacity);
}

int compare(const void * a, const void * b)
{
    Node *node_a = *(Node**)a;
    Node *node_b = *(Node**)b;
    if(node_a->count != node_b->count)
    {
        return node_b->count - node_a->count;
    }
    return strlen(node_a->word) - strlen(node_b->word);
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
                printf("Enter the number: ");
                int count_world;
                if(scanf("%d", &count_world) != 1)
                {
                    printf("incorrect number\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                int len = 0, capacity = 2;
                Node ** array = (Node **) malloc(capacity * sizeof(Node *));
                if(array == NULL)
                {
                    return 0;
                }
                collect_nodes(root, &array, &len, &capacity);
                for(int i = 0; i < len; ++i)
                {
                    printf("%s ", array[i]->word);
                }
                printf("\n");

                qsort(array, len, sizeof(Node**), compare);
                for(int i = 0; i < len && i < count_world; ++i)
                {
                    printf("%s ", array[i]->word);
                }
                printf("\n");

                free(array);
                break;
            case '3':
                Node * min = root;
                Node * max = root;
                search_max_min_word(root, &min, &max);
                printf("minimum word length: %s\n", min->word);
                printf("maximum word length: %s\n", max->word);
                break;
            case '4':
                int depth = max_depth(root);
                printf("depth = %d\n", depth);
                break;
            case '5':
                const char filename[9] = "tree.txt";
                FILE * file = fopen(filename, "w");
                inorder(root, 0);
                preorder(file, root, separator);
                fclose(file);
                root = delete_tree(root);

                file = fopen(filename, "r");
                read_from_file(file, &root, separator);
                printf("\n\n");
                inorder(root, 0);
                fclose(file);

                printf("outputting the tree to a file and restoring it is done\n");
                break;
            case '6':
                flag_stop = 1;
                break;
            default:
                printf("select a number from the menu\n");
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