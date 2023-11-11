#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* array;
    int length;
} String;

//что делать со строкой nullx

String * string_create(char * input_str)
{
    String * str = (String *)malloc(sizeof(String));
    if(str == NULL)
    {
        return NULL;
    }
    str->length = strlen(input_str);
    //что если пришел NUll?
    str->array = (char *)malloc((str->length + 1) * sizeof(char));
    if(str->array == NULL)
    {
        free(str);
        return NULL;
    }
    strcpy(str->array, input_str);
    return str;
}

void delete_string_content(String * str)
{
    free(str->array);
    str->length = 0;
    str->array = NULL;
}

int string_order_relation(const String * str1, const String * str2)
{
    if(str1->length != str2->length)
    {
        return str1->length - str2->length;
    }
    return strcmp(str1->array, str2->array);
}

int string_equivalence_relations(const String * str1, const String * str2)
{
    return strcmp(str1->array, str2->array) == 0;
}

String * copy_to_new_string(const String * str)
{
    String * new_str = (String *)malloc(sizeof(String));
    if(new_str == NULL)
    {
        return NULL;
    }
    new_str->array = (char *) malloc((str->length + 1) * sizeof(char));
    if(new_str->array == NULL)
    {
        free(new_str);
        return NULL;
    }
    strcpy(new_str->array, str->array);
    new_str->length = str->length;
    return new_str;
}

String * string_concatenation(String * str1, const String * str2)
{
    char * for_realloc = (char *) realloc(str1->array, str1->length + str2->length + 1);
    if(for_realloc == NULL)
    {
        return NULL;
    }
    str1->array = for_realloc;
    strcat(str1->array, str2->array);
    str1->length += str2->length;
    return str1;
}

String * string_destroy(String * str)
{
    free(str->array);
    free(str);
    return NULL;
}

//int main()
//{
//
//    String * str1 = string_create("lol");
//    printf("string: %s, %d\n", str1->array, str1->length);
//
//    String * str2 = string_create("hello");
//    printf("string: %s, %d\n", str2->array, str2->length);
//
//    printf("order_relation: %d\n", string_order_relation(str1, str2));
//
//    printf("equivalence_relations: %d\n", string_equivalence_relations(str1, str2));
//
//    String * str3 = copy_to_new_string(str1);
//    printf("copy_to_new_string: %s, %d\n", str2->array, str2->length);
//
//    delete_string_content(str1);
//    printf("string with delete content: %s, %d\n", str1->array, str1->length);
//
//    string_concatenation(str2, str3);
//    printf("string_concatenation: %s, %d\n", str2->array, str2->length);
//
//    string_destroy(str1);
//    string_destroy(str2);
//    string_destroy(str3);
//    return 0;
//}
