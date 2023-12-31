#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    int cmp = strcmp(word, root->word);
    if(cmp == 0)
    {
        root->count++;
    }
    else if(cmp < 0)
    {
        root->left = insert_node(root->left, word);
    }
    else
    {
        root->right = insert_node(root->right, word);
    }

    return root;
}

Node * search_node(Node * root, char * word)
{
    if (root == NULL)
    {
        return NULL;
    }

    int cmp = strcmp(word, root->word);
    if(cmp == 0)
    {
        return root;
    }
    else if(cmp < 0)
    {
        return search_node(root->left, word);
    }
    else
    {
        return search_node(root->right, word);
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
           "5. Saving a tree to a file\n"
           "6. Restoring a tree from file\n"
           "7. Exit\n"
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

enum errors collect_nodes(Node* node, Node*** nodes, int* len, int* capacity)
{
    enum errors err = OK;
    if (node == NULL)
    {
        return OK;
    }

    err = collect_nodes(node->left, nodes, len, capacity);
    if(err == INVALID_MEMORY) return INVALID_MEMORY;

    if (*len == *capacity)
    {
        *capacity *= 2;
        Node** for_realloc = (Node **)realloc(*nodes, *capacity * sizeof(Node*));
        if (for_realloc == NULL)
        {
            return INVALID_MEMORY;
        }
        *nodes = for_realloc;
    }

    (*nodes)[*len] = node;
    (*len)++;

    err = collect_nodes(node->right, nodes, len, capacity);
    if(err == INVALID_MEMORY) return INVALID_MEMORY;

    return err;
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

void generate_filename(char * str)
{
    srand(time(NULL));
    for (int i = 0; i < 5; ++i)
    {
        str[i] = rand() % 95 + 33;
    }
    str[5] = '\0';
    strcat(str, ".txt");
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

    fclose(filename);

    inorder(root, 0);

    int cap_temp = 10;
    char * temp_file = (char *) malloc(cap_temp * sizeof(char ));
    if(temp_file == NULL)
    {
        printf("memory allocation error\n");
        free(separator);
        root = delete_tree(root);
        return INVALID_MEMORY;
    }
    generate_filename(temp_file);

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
                if(root == NULL)
                {
                    printf("The tree is empty\n"
                           "I can't find the number of words in an empty tree\n");
                    break;
                }

                int capacity_buffer = 20;
                char * buff = (char *) malloc(capacity_buffer * sizeof(char));
                if(buff == NULL)
                {
                    free(separator);
                    free(temp_file);
                    delete_tree(root);
                    printf("memory allocation error\n");
                    return INVALID_MEMORY;
                }
                printf("Enter a search word: ");
                char c;
                int idx = 0;
                c = getchar();
                while(c != '\n')
                {
                    buff[idx++] = c;
                    if(idx == capacity_buffer)
                    {
                        capacity_buffer *= 2;
                        char * for_realloc = (char *) realloc(buff, capacity_buffer);
                        if(for_realloc == NULL)
                        {
                            free(separator);
                            free(temp_file);
                            delete_tree(root);
                            printf("memory allocation error\n");
                            return INVALID_MEMORY;
                        }
                        buff = for_realloc;
                    }
                    c = getchar();
                }
                buff[idx] = '\0';

                Node * search = search_node(root, buff);
                if(search == NULL)
                {
                    printf("number of words '%s' found in the text: %d\n", buff, 0);
                }
                else
                {
                    printf("number of words '%s' found in the text: %d\n", search->word, search->count);
                }
                free(buff);
                break;
            case '2':
                if(root == NULL)
                {
                    printf("The tree is empty\n"
                           "I can't print n frequently occurring words\n");
                    break;
                }

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
                    free(array);
                    free(separator);
                    delete_tree(root);
                    free(temp_file);
                    printf("memory allocation error\n");
                    return INVALID_MEMORY;
                }
                if (collect_nodes(root, &array, &len, &capacity) != OK)
                {
                    free(array);
                    free(separator);
                    delete_tree(root);
                    free(temp_file);
                    printf("memory allocation error\n");
                    return INVALID_MEMORY;
                }
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
                if(root == NULL)
                {
                    printf("The tree is empty\n"
                           "I can't figure out the shortest and longest word\n");
                    break;
                }

                Node * min = root;
                Node * max = root;
                search_max_min_word(root, &min, &max);
                printf("minimum word length: %s\n", min->word);
                printf("maximum word length: %s\n", max->word);
                break;
            case '4':
                if(root == NULL)
                {
                    printf("The tree is empty\n");
                }

                int depth = max_depth(root);
                printf("depth = %d\n", depth);
                break;
            case '5':
                if(root == NULL)
                {
                    printf("The tree is empty\n");
                }

                printf("file: %s\n", temp_file);

                FILE * file = fopen(temp_file, "w");
                if(file == NULL)
                {
                    printf("Error opening file %s\n", temp_file);
                    free(separator);
                    free(temp_file);
                    delete_tree(root);
                    return ERROR_OPEN_FILE;
                }

                printf("The tree before saving to a file looks like this:\n");
                if(root == NULL)
                    printf("\n");
                else
                    inorder(root, 0);
                preorder(file, root, separator);
                fclose(file);
                root = delete_tree(root);

                printf("outputting the tree to a file is done\n");
                break;
            case '6':
                if(root == NULL)
                {
                    printf("The tree is empty\n");
                }

                file = fopen(temp_file, "r");
                if(file == NULL)
                {
                    printf("Error opening file %s\n", temp_file);
                    free(separator);
                    delete_tree(root);
                    free(temp_file);
                    return ERROR_OPEN_FILE;
                }

                read_from_file(file, &root, separator);
                printf("The tree after restoration from the file looks like this:\n");
                if(root == NULL)
                    printf("\n");
                else
                    inorder(root, 0);
                fclose(file);
                break;
            case '7':
                flag_stop = 1;
                break;
            default:
                printf("select a number from the menu\n");
                break;
        }
        if(!flag_stop) printf("Select option: ");
    }

    free(temp_file);
    free(separator);
    delete_tree(root);

    return 0;
}