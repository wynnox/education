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
            srand(time(NULL));
            int size_of_array_a = rand() % (100 + 1 - 10) + 10;
            printf("%d\n", size_of_array_a);
            int size_of_array_b = rand() % (100 + 1 - 10) + 10;
            printf("%d\n", size_of_array_b);
            short * array_a = NULL;
            short * array_b = NULL;
            short * array_c = NULL;
            if(array_generation_of_task2(-1000, 1000, &array_a, size_of_array_a) != OK ||
                array_generation_of_task2(-1000, 1000, &array_b, size_of_array_b) != OK)
            {
                printf("Ошибка: ошибка с памятью 2\n");
                free(array_a);
                free(array_b);
                return INVALID_MEMORY;
            }

            if(generate_array_and_find_closest(&array_a, size_of_array_a, &array_b, size_of_array_b, &array_c) != OK)
            {
                printf("Ошибка: ошибка с памятью 3\n");
                return INVALID_MEMORY;
            }
            printf("массив a\n");
            for (int i = 0; i < size_of_array_a; ++i)
            {
                printf("%d ", array_a[i]);
            }
            printf("\nмассив b\n");
            for (int i = 0; i < size_of_array_b; ++i)
            {
                printf("%d ", array_b[i]);
            }

            printf("\nмассив c\n");
            for (int i = 0; i < size_of_array_a; ++i)
            {
                printf("%d ", array_c[i]);
            }
            free(array_a);
            free(array_b);
            free(array_c);
            break;
        default:
            printf("Ошибка: некорректный ввод");
            return INVALID_INPUT;
    }
    return 0;
}