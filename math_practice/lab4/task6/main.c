#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>


#define SIZE 20
#define SIZE_OUTPUT 10
#define SIZE_OPERAND 26

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

        if (isdigit(c))
        {
            (*postfix)[idx++] = c;
        }
        else if(isalpha(c))
        {
            c = toupper(c);
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
            if (c == '~')
            {
                Stack_char_push(&Stack_char, c);
            }
            else
            {
                while (Stack_char != NULL && precedence(c) <= precedence(Stack_char->value))
                {
                    (*postfix)[idx++] = Stack_char->value;
                    Stack_char_pop(&Stack_char, &temp);
                }
                Stack_char_push(&Stack_char, c);
            }
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

void print_error(FILE * output, enum errors err)
{
    switch (err)
    {
        case INVALID_INPUT:
            fprintf(output, "invalid operand\n");
            break;
        case EMPTY_LINE:
            fprintf(output, "empty line\n");
            break;
        case EMPTY_BRACKET:
            fprintf(output, "empty bracket\n");
            break;
        case INVALID_BRACKET:
            fprintf(output, "invalid bracket\n");
            break;
        case UNUSED_DIGITS_OR_OPERATORS:
            fprintf(output, "invalid infix\n");
            break;
        default:
            fprintf(output, "????\n");
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

            if(postfix[i] == '~')
            {
                Stack_node_push(&stack, node);
                continue;
            }

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

void generateFileName(char* filename, int length)
{
    srand((unsigned int)(time(NULL)));

    for(int i = 0; i < length - 5; i++)
    {
        if(rand() % 2 == 0)
        {
            filename[i] = 'a' + rand() % 26;
        } else {
            filename[i] = '0' + rand() % 10;
        }
    }
    filename[length - 5] = '\0';
    strcat(filename, ".txt");
}

void extract_operands(const char* postfix, char* operands)
{
    int idx = 0;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];
        if (isalpha(c))
        {
            c = toupper(c);
            bool isUnique = true;
            for (int j = 0; j < idx; j++) {
                if (operands[j] == c)
                {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique)
            {
                operands[idx++] = c;
            }
        }
    }
    operands[idx] = '\0';
}

int evaluate(Node* root, char * operand, int mask)
{
    if (root == NULL)
        return 0;

    if (!is_operator(root->value))
    {
        if(isalpha(root->value))
        {
            int idx = strchr(operand, root->value) - operand;
            return (mask & (1 << idx)) ? 1 : 0;
        }
        else
        {
            return root->value - '0';
        }
    }

    int leftValue = evaluate(root->left, operand, mask);
    int rightValue = evaluate(root->right, operand, mask);

    switch (root->value)
    {
        case '&':
            return (leftValue && rightValue);
        case '|':
            return (leftValue || rightValue);
        case '~':
            return !rightValue;
        case '-':
            return !leftValue || rightValue;
        case '+':
            return (leftValue && !rightValue);
        case '<':
            return (leftValue ^ rightValue);
        case '=':
            return leftValue == rightValue;
        case '!':
            return !leftValue && !rightValue;
        case '?':
            return !(leftValue || rightValue);
        default:
            return false;
    }
    return 0;
}

int is_binary_operation(char symbol)
{
    return ((symbol == '?') || (symbol == '!') || (symbol == '+') ||
            (symbol == '&') || (symbol == '|') || (symbol == '-') ||
            (symbol == '>') || (symbol == '=') || (symbol == '>'));
}

int is_operand(char c)
{
    if(isalpha(c))
    {
        return 1;
    }
    else
    {
        return c == '0' || c == '1';
    }
}


int check_valid(char * infix)
{
    int len = strlen(infix);
    if(is_binary_operation(infix[0]) || infix[0] == ')'
       || infix[len - 1] == '(' || is_binary_operation(infix[len - 1]) || infix[len - 1] == '~')
    {
        return 0;
    }
    for(int i = 0; i < len - 1; ++i)
    {
        int a = infix[i], b = infix[i+1];
        if(is_operand(a) && is_operand(b)) return 0;
        if((a == '(' || a == ')') && (b == '(' || b == ')') && (a != b)) return 0;
        if((is_binary_operation(a) || a == '~') && (b == ')')) return 0;
        if(a == '(' && (is_binary_operation(b) || b == '~')) return 0;
        if((is_binary_operation(a) || a == '~') && (is_binary_operation(b))) return 0;
        if(a == '(' && is_operand(b)) return 0;
        if(is_operand(a) && b == ')') return 0;
    }
    return 1;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s file.txt\n", argv[0]);
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

    char * output = (char *) malloc(sizeof(char) * (SIZE_OUTPUT + 1));
    if(output == NULL)
    {
        printf("memory allocation error\n");
        free(infix);
        return INVALID_MEMORY;
    }

    char * operand = (char *) malloc(sizeof(char ) * (SIZE_OPERAND + 1));
    if(operand == NULL)
    {
        printf("memory allocation error\n");
        free(infix);
        free(output);
        return INVALID_MEMORY;
    }

    enum errors err;

    input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    printf("file: %s\n", argv[1]);

    generateFileName(output, SIZE_OUTPUT);

    FILE * stream_output = fopen(output, "w");
    if(stream_output == NULL)
    {
        printf("Error opening file %s\n", output);
        return ERROR_OPEN_FILE;
    }

    printf("file_out: %s\n", output);

    err = read_string(input, &infix, &capacity_infix);

    if(err == INVALID_MEMORY)
    {
        printf("memory allocation error\n");
        free(infix);
        free(output);
        fclose(stream_output);
        fclose(input);
        free(operand);
        return INVALID_MEMORY;
    }
    else if(err != OK)
    {
        print_error(stream_output, err);
        fclose(stream_output);
        fclose(input);
        free(infix);
        free(output);
        free(operand);
        return err;
    }


    char * postfix = (char *) malloc(sizeof(char) * ( 3 * strlen(infix) + 1));
    if(postfix == NULL)
    {
        fclose(stream_output);
        fclose(input);
        free(infix);
        free(output);
        free(operand);
        return INVALID_MEMORY;
    }

    int check = check_valid(infix);
    if(check == 0)
    {
        print_error(stream_output, UNUSED_DIGITS_OR_OPERATORS);
        fclose(stream_output);
        fclose(input);
        free(infix);
        free(output);
        free(postfix);
        free(operand);
        return UNUSED_DIGITS_OR_OPERATORS;
    }

    err = infix_to_postfix(infix, &postfix);
    if(err != OK)
    {
        print_error(stream_output, err);
        fclose(stream_output);
        fclose(input);
        free(infix);
        free(output);
        free(postfix);
        free(operand);
        return err;
    }

    Node * root = build_tree(postfix);

    inorder(root, 0);

    extract_operands(postfix, operand);

    int count_operand = strlen(operand);
    if(count_operand == 0)
    {
        fprintf(stream_output, "infix: %s\npostfix: %s\n", infix, postfix);
        int res = evaluate(root, operand, count_operand);
        fprintf(stream_output, "result: %d", res);
    }
    else
    {
        fprintf(stream_output, "infix: %s\npostfix: %s\n", infix, postfix);
        for(int i = 0; i < count_operand; ++i)
        {
            fprintf(stream_output, "\t%c\t|", operand[i]);
        }
        fprintf(stream_output, "\t%s\n", infix);
        for(int i = 0; i < pow(2, count_operand); ++i)
        {
            for(int j = 0; j < (count_operand); ++j)
            {
                int k = (i & (1 << j)) ? 1 : 0;
                fprintf(stream_output, "\t%d\t|", k);
            }
            int res = evaluate(root, operand, i);
            fprintf(stream_output, "\t%d\n", res);
        }
    }

    delete_tree(root);
    fclose(stream_output);
    fclose(input);
    free(infix);
    free(output);
    free(postfix);
    free(operand);

    return 0;
}