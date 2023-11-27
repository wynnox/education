#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//#define SIZE_HASH 128
#define SIZE_HASH 6
#define EPSILON 1e-6

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE
};

typedef struct Ht_item
{
    int hash;
    char * key;
    char * value;
    struct Ht_item * next;
} Ht_item;

typedef struct Hash_Table
{
    Ht_item ** items;
    int size;
} Hash_Table;

Hash_Table * create_table(int size_hash)
{
    Hash_Table * table = (Hash_Table *) malloc(sizeof(Hash_Table));
    if(table == NULL)
    {
        return NULL;
    }
    table->size = size_hash;

    table->items = (Ht_item**) calloc(size_hash, sizeof(Ht_item*));
    if(table->items == NULL)
    {
        free(table);
        return NULL;
    }
    return table;
}

int hash_function(char* key)
{
    int num = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        if (key[i] >= '0' && key[i] <= '9')
            num = num*62 + key[i] - '0';
        else if (key[i] >= 'A' && key[i] <= 'Z')
            num = num*62 + key[i] - 'A' + 10;
        else if (key[i] >= 'a' && key[i] <= 'z')
            num = num*62 + key[i] - 'a' + 36;
    }
    return num;
}

Ht_item * create_item(char* key, char* value)
{
    Ht_item * item = (Ht_item *)malloc(sizeof(Ht_item));
    if(item == NULL)
    {
        return NULL;
    }

    item->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
    if(item->key == NULL)
    {
        free(item);
        return NULL;
    }
    strcpy(item->key, key);

    item->value = (char *) malloc((strlen(value) + 1) * sizeof(char));
    if(item->value == NULL)
    {
        free(item->key);
        free(item);
        return NULL;
    }
    strcpy(item->value, value);

    item->next = NULL;
    item->hash = 0;
    return item;
}

void destroy_item(Ht_item* item)
{
    free(item->key);
    free(item->value);
    free(item);
}

Hash_Table * destroy_hashtable(Hash_Table * table)
{
    for(int i = 0; i < table->size; ++i)
    {
        Ht_item* item = table->items[i];
        while(item != NULL)
        {
            Ht_item* next = item->next;
            destroy_item(item);
            item = next;
        }
    }
    free(table->items);
    free(table);
    return NULL;
}

void insert(Hash_Table* table, char* key, char* value)
{
    int hash = hash_function(key);
    int index = hash % table->size;

    Ht_item * item = create_item(key, value);
    item->hash = hash;

    if (table->items[index] == NULL)
    {
        table->items[index] = item;
    }
    else
    {
        Ht_item* current = table->items[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = item;
    }
}

void print_hashtable(Hash_Table *table)
{
    for (int i = 0; i < table->size; ++i)
    {
        if(table->items[i])
        {
            printf("Bucket %d:\n", i);

            Ht_item *current = table->items[i];
            while (current != NULL)
            {
                printf("  Key: %s, Value: %s\n", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

enum errors read_str(FILE * input, char ** buffer, int * capacity, char * c)
{
    int idx = 0;
    *c = fgetc(input);
    while(*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF)
    {
        (*buffer)[idx++] = *c;
        if(*capacity == idx)
        {
            *capacity *= 2;
            char * for_realloc = (char *) realloc(*buffer, *capacity);
            if(for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *buffer = for_realloc;
        }
        *c = fgetc(input);
    }
    (*buffer)[idx] = '\0';
    return OK;
}

enum errors read_define(FILE * input, Hash_Table *table, char ** str, char * c, int * capacity_str)
{
    int capacity_key = 20, capacity_value = 20;
    char * key = (char *)malloc(capacity_key * sizeof(char));
    if(key == NULL)
    {
        return INVALID_MEMORY;
    }
    char * value = (char *)malloc(capacity_value * sizeof(char));
    if(value == NULL)
    {
        free(key);
        return INVALID_MEMORY;
    }

    while(!feof(input))
    {
        read_str(input, str, capacity_str, c);
        if(strcmp("#define", *str) == 0)
        {
            if (read_str(input, &key, &capacity_key, c) != OK)
            {
                free(key);
                free(value);
                return INVALID_MEMORY;
            }
            if (read_str(input, &value, &capacity_value, c) != OK)
            {
                free(key);
                free(value);
                return INVALID_MEMORY;
            }
            insert(table, key, value);
        }
        else
        {
            break;
        }
    }

    free(key);
    free(value);
    return OK;
}

int check_needs_rebuilt(HashTable* table)
{
    int min = INT_MAX;
    int max = 0;
    for (int i = 0; i < table->size; i++)
    {
        int current_len = 0;
        Ht_item* item = table->items[i];
        while (item != NULL)
        {
            current_len++;
            item = item->next;
        }
        if (current_len < min) {
            min = chainLen;
        }
        if (current_len > max) {
            max = chainLen;
        }
    }
    double res = max / min;
    if(res - 2 > EPSILON)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void rebuild_hashtable(HashTable* table, int new_size)
{

}

//enum errors replace_text()
//{
//    return OK;
//}

int main(int agrc, char * argv[])
{
    if(agrc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE * filename = fopen(argv[1], "r");
    if(filename == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return ERROR_OPEN_FILE;
    }

    FILE * temp = fopen("temp.txt", "w");
    if(temp == NULL)
    {
        printf("Error opening file\n");
        return ERROR_OPEN_FILE;
    }

    Hash_Table * table = create_table(SIZE_HASH);
    if(table == NULL)
    {
        printf("memory allocation error\n");
        fclose(filename);
        return INVALID_MEMORY;
    }

    int capacity = 20;
    char c;
    char * buffer = (char *)malloc(capacity * sizeof(char));
    if(buffer == NULL)
    {
        destroy_hashtable(table);
        fclose(filename);
        fclose(temp);
        printf("memory allocation error\n");
        return INVALID_MEMORY;
    }

    /*
     * если одинаковый ключ, то все равно добавляет, надо проверить на это
     * value может быть разделитемем спокойно, так что надо допилить
     *
     * пересборка
     * чтение и замена, скидывание в файл темп
     * закрытие и открытие файлов, туда кидаем из темпа
     */

    if(read_define(filename, table, &buffer, &c, &capacity) != OK)
    {
        destroy_hashtable(table);
        fclose(filename);
        fclose(temp);
        free(buffer);
        printf("memory allocation error\n");
        return INVALID_MEMORY;
    }
    printf("hash table created\n");
    print_hashtable(table);

    if(check_needs_rebuilt(table))
    {
        printf("hash table after rebuild\n");
        print_hashtable(table);
    }
    else
    {
        printf("hash table is not rebuilt\n");
    }




    free(buffer);
    destroy_hashtable(table);
    fclose(filename);
    fclose(temp);
    return 0;
}