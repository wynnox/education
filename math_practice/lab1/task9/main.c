#include "array_operations.h"

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 3:
            long int start, stop;
            if(convert_str_to_int(argv[1], &start, 10) != OK ||
                convert_str_to_int(argv[2], &stop, 10) != OK ||
                start > stop)
            {
                printf("Ошибка: инвалидный ввод\n");
                return INVALID_INPUT;
            }
            long int* result_array = NULL;
            int size_of_array = 20;
            if(array_generation(start, stop, &result_array, size_of_array) != OK)
            {
                printf("Ошибка: ошибка с память\n");
                free(result_array);
                return INVALID_MEMORY;
            }
            printf("Исходный массив:\n");
            for(int i = 0; i < size_of_array; ++i)
            {
                printf("%ld ", result_array[i]);
            }
            printf("\n");
            swap_min_max_in_array(&result_array, size_of_array);
            printf("Получившийся массив:\n");
            for(int i = 0; i < size_of_array; ++i)
            {
                printf("%ld ", result_array[i]);
            }
            printf("\n");
            free(result_array);
            break;
        case 1:

            break;
        default:
            printf("Ошибка: некорректный ввод");
            return INVALID_INPUT;
    }
    return 0;
}