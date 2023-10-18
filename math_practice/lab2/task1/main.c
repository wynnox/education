#include "string_operations_with_flag.h"

int main(int argc, char * argv[])
{
    if(argc < 3 || argv[1][0] != '-')
    {
        printf("invalid input\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
    case 'l':
        if(argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        int len = string_len(argv[2]);
        printf("%d\n", len);
        break;
    case 'r':
        if(argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        char * result_r;
        if(string_reverse(argv[2], &result_r) != OK)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("%s\n", result_r);
        free(result_r);
        break;
    case 'u':
        if(argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        char * result_u;
        if(convert_odd_chars_to_upper(argv[2], &result_u) != OK)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("%s\n", result_u);
        free(result_u);
        break;
    case 'n':
        if(argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        char * result_n;
        if(reorder_string(argv[2], &result_n) != OK)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("%s\n", result_n);
        free(result_n);
        break;
    case 'c':
        int count_str = argc - 3;
        if(count_str == 0)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        unsigned int seed;
        if(convert_str_to_int(argv[2], &seed, 10) != OK)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        char * result_c;
        if(concatenate_randomly((argv + 3), count_str, &result_c, seed) != OK)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("%s\n", result_c);
        free(result_c);
        break;
    default:
        printf("invalid flag\n");
        break;
    }
    return OK;
}