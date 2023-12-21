#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "ctype.h"

#define SIZE 20

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    DIVISION_BY_ZERO,
    EMPTY_LINE,
    EMPTY_BRACKET,
    INVALID_BRACKET,
    NEGATIVE_MOD,
    NEGATIVE_POWER,
    UNUSED_DIGITS_OR_OPERATORS
};

typedef struct Node {
    char value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Stack_char
{
    char value;
    struct Stack_char * next;
} Stack_char;

typedef struct Stack_node
{
    Node* value;
    struct Stack_node * next;
} Stack_node;


enum errors Stack_char_push(Stack_char ** head, char data)
{
    Stack_char * tmp = (Stack_char*) malloc(sizeof(Stack_char));
    if(tmp == NULL)
    {
        return INVALID_MEMORY;
    }
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
    return OK;
}

enum errors Stack_char_pop(Stack_char ** head, char * num)
{
    Stack_char* prev = NULL;
    if (head == NULL || *head == NULL)
    {
        return INVALID_INPUT;
    }

    prev = (*head);
    *num = prev->value;
    (*head) = (*head)->next;

    free(prev);
    return OK;
}

void Stack_char_free(Stack_char * head)
{
    Stack_char * tmp = NULL;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

enum errors Stack_node_push(Stack_node ** head, Node* data)
{
    Stack_node * tmp = (Stack_node*) malloc(sizeof(Stack_node));
    if(tmp == NULL)
    {
        return INVALID_MEMORY;
    }
    tmp->value = data;
    tmp->next = *head;
    *head = tmp;
    return OK;
}

enum errors Stack_node_pop(Stack_node ** head, Node** num)
{
    Stack_node* prev = NULL;
    if (head == NULL || *head == NULL)
    {
        return INVALID_INPUT;
    }

    prev = (*head);
    *num = prev->value;
    (*head) = (*head)->next;

    free(prev);
    return OK;
}

int is_operator(const char symbol)
{
    return ((symbol == '(') || (symbol == ')') || (symbol == '~') ||
            (symbol == '?') || (symbol == '!') || (symbol == '+') ||
            (symbol == '&') || (symbol == '|') || (symbol == '-') ||
            (symbol == '<') || (symbol == '='));
}

int precedence(char c)
{
    switch (c)
    {
        case '~':
            return 3;
        case '?':
        case '!':
        case '+':
        case '&':
            return 2;
        case '|':
        case '-':
        case '<':
        case '=':
            return 1;
        default:
            return 0;
    }
}

enum errors infix_to_postfix(const char *infix, char **postfix)
{
    Stack_char *Stack_char = NULL;
    int idx = 0;

    char c;
    char temp;
    int len = strlen(infix);
    for (int i = 0; i < len; ++i)
    {
        c = infix[i];

        if (isdigit(c) || isalpha(c))
        {
            (*postfix)[idx++] = c;
        }
        else if (c == '(')
        {
            if (i < len - 1 && infix[i + 1] == ')')
                return EMPTY_BRACKET;
            Stack_char_push(&Stack_char, c);
        }
        else if (c == ')')
        {
            while (Stack_char != NULL && Stack_char->value != '(')
            {
                (*postfix)[idx++] = Stack_char->value;
                Stack_char_pop(&Stack_char, &temp);
            }

            if (Stack_char != NULL && Stack_char->value == '(')
                Stack_char_pop(&Stack_char, &temp);
            else
                return INVALID_BRACKET;
        }
        else if (is_operator(c))
        {
            while (Stack_char != NULL && precedence(c) <= precedence(Stack_char->value))
            {
                (*postfix)[idx++] = Stack_char->value;
                Stack_char_pop(&Stack_char, &temp);
            }
            Stack_char_push(&Stack_char, c);
            if(c == '-' || c == '+' || c == '<') i++;
        }
        else
        {
            return INVALID_INPUT;
        }
    }

    while (Stack_char != NULL && Stack_char->value != '(')
    {
        (*postfix)[idx++] = Stack_char->value;
        Stack_char_pop(&Stack_char, &temp);
    }

    if (Stack_char != NULL)
    {
        while(Stack_char != NULL)
            Stack_char_pop(&Stack_char, &temp);
        return INVALID_BRACKET;
    }

    (*postfix)[idx] = '\0';

    return OK;
}

enum errors read_string(FILE * input, char ** infix, int * capacity_infix)
{
    int idx = 0;
    char c = fgetc(input);

    if(c == EOF)
    {
        (*infix)[idx] = '\0';
        return EMPTY_LINE;
    }

    while(c != EOF)
    {
        if(idx + 1 >= *capacity_infix)
        {
            (*capacity_infix) *= 2;
            char * for_realloc = (char *) realloc(*infix, *capacity_infix);
            if(for_realloc == NULL) return INVALID_MEMORY;
            *infix = for_realloc;
        }
        (*infix)[idx++] = c;
        c = fgetc(input);
        if(c == '\n') return INVALID_INPUT;
    }

    (*infix)[idx] = '\0';

    return OK;
}

void print_error(FILE * output, enum errors err, int count_line)
{
    switch (err)
    {
        case INVALID_INPUT:
            fprintf(output, "№%d: invalid operand\n", count_line);
            break;
        case DIVISION_BY_ZERO:
            fprintf(output, "№%d: division by zero\n", count_line);
            break;
        case EMPTY_LINE:
            fprintf(output, "№%d: empty line\n", count_line);
            break;
        case EMPTY_BRACKET:
            fprintf(output, "№%d: empty bracket\n", count_line);
            break;
        case INVALID_BRACKET:
            fprintf(output, "№%d: invalid bracket\n", count_line);
            break;
        case NEGATIVE_MOD:
            fprintf(output, "№%d: negative mod\n", count_line);
            break;
        case NEGATIVE_POWER:
            fprintf(output, "№%d: negative power\n", count_line);
            break;
        case UNUSED_DIGITS_OR_OPERATORS:
            fprintf(output, "№%d: unused operand or operation\n", count_line);
            break;
        default:
            fprintf(output, "№%d: ????\n", count_line);
            break;
    }
}

Node* create_node(char value)
{
    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL) return NULL;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* build_tree(const char* postfix)
{
    Stack_node* stack = NULL;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isdigit(postfix[i]) || isalpha(postfix[i]))
        {
            Node* node = create_node(postfix[i]);
            Stack_node_push(&stack, node);
        }
        else if (is_operator(postfix[i]))
        {
            Node* node = create_node(postfix[i]);

            Node* right = NULL;
            Stack_node_pop(&stack, &right);
            node->right = right;

            Node* left = NULL;
            Stack_node_pop(&stack, &left);
            node->left = left;

            Stack_node_push(&stack, node);
        }
    }

    Node * node;
    Stack_node_pop(&stack, &node);


    return node;
}

void inorder(Node* root, int depth)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, depth + 1);
    for (int i = 0; i < depth * 3; i++) {
        printf(" ");
    }
    printf("\\_%c\n", root->value);
    inorder(root->right, depth + 1);
}

Node * delete_tree(Node* root) {
    if (root)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
    return NULL;
}

int main(int argc, char * argv[])
{
    if(argc == 1)
    {
        printf("Usage: %s file1.txt file2.txt ...\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * input = NULL;
    int capacity_infix = SIZE;
    char * infix = (char *) malloc(sizeof(char) * capacity_infix);
    if(infix == NULL)
    {
        printf("memory allocation error\n");
        return INVALID_MEMORY;
    }

    enum errors err;
    for (int i = 1; i < argc; ++i)
    {
        input = fopen(argv[i], "r");
        if(input == NULL)
        {
            printf("Error opening file %s\n", argv[i]);
            continue;
        }

        printf("file: %s\n", argv[i]);

        err = read_string(input, &infix, &capacity_infix);

        if(err == INVALID_MEMORY)
        {
            printf("memory allocation error\n");
            fclose(input);
            free(infix);
            return INVALID_MEMORY;
        }
        else if(err != OK)
        {
//            print_error(err_output, err, count_line);
            continue;
        }

        char * postfix = (char *) malloc(sizeof(char) * ( 3 * strlen(infix) + 1));
        if(postfix == NULL)
        {
            fclose(input);
            free(infix);
            return INVALID_MEMORY;
        }

        err = infix_to_postfix(infix, &postfix);
        if(err != OK)
        {
            free(postfix);
            printf("!!");
            continue;
        }

        printf("%s %s\n", infix, postfix);

        Node * root = build_tree(postfix);

        inorder(root, 0);


        free(postfix);
    }

    free(infix);
    return 0;
}