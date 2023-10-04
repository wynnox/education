#include "math_calc_with_flags.h"

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }

    if( !((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0') ) {
        printf("Ошибка: некорректный ввод");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
        case 'q':
            if(argc != 6)
            {
                printf("Ошибка: некорректный ввод\n");
                return INVALID_INPUT;
            }

            double epsilon_q, coefficient1, coefficient2, coefficient3 ;
            if (convert_str_to_double(argv[2], &epsilon_q) != OK ||
                epsilon_q < 0 ||
                convert_str_to_double(argv[3], &coefficient1) != OK ||
                convert_str_to_double(argv[4], &coefficient2) != OK ||
                convert_str_to_double(argv[5], &coefficient3) != OK)
            {
                printf("Ошибка: некорректный ввод чисел\n");
                return INVALID_INPUT;
            }
            int size_array = 3;
            double * array_coefficient = (double *) malloc(sizeof(double ) * size_array);
            array_coefficient[0] = coefficient1;
            array_coefficient[1] = coefficient2;
            array_coefficient[2] = coefficient3;
            int max_permutations = 6;
            int count_permutation = 0;
            double ** result = (double **)malloc(sizeof(double*) * max_permutations);
            for(int i = 0; i < max_permutations; ++i)
            {
                result[i] = (double *) malloc(size_array * sizeof(double));
            }
            result[0][1] = coefficient1;
            result[0][2] = coefficient2;
            result[0][3] = coefficient3;
            permutation(&result, array_coefficient, size_array, &count_permutation, size_array, epsilon_q);

            for(int i = 0; i <= count_permutation; ++i)
            {
                for(int j = 0; j < size_array; ++j)
                {
                    printf("%lf ", result[i][j]);
                }
                printf("\n");
            }

            for(int i = 0; i < count_permutation; i++)
                free(result[i]);
            free(result);
            free(array_coefficient);
            break;
        case 'm':

            if (argc != 4)
            {
                printf("Ошибка: некорректный ввод\n");
                return INVALID_INPUT;
            }
            long int num1, num2;
            if (convert_str_to_int(argv[2], &num1, 10) != OK ||
                convert_str_to_int(argv[3], &num2, 10) != OK ||
                num1 == 0 || num2 == 0)
            {
                printf("Ошибка: слишком большое число или 0\n");
                return INVALID_INPUT;
            }
            if(num1 % num2 == 0)
            {
                printf("Число %ld делится на %ld без остатка\n", num1, num2);
            }
            else
            {
                printf("Число %ld НЕ делится на %ld без остатка\n", num1, num2);
            }
            break;

        case 't':

            if (argc != 6)
            {
                printf("Ошибка: некорректный ввод\n");
                return INVALID_INPUT;
            }
            double epsilon_t, side1, side2, side3;
            if (convert_str_to_double(argv[2], &epsilon_t) != OK ||
                epsilon_t <= 0 ||
                convert_str_to_double(argv[3], &side1) != OK ||
                convert_str_to_double(argv[4], &side2) != OK ||
                convert_str_to_double(argv[5], &side3) != OK)
            {
                printf("Ошибка: некорректный ввод значений\n");
                return INVALID_INPUT;
            }
            //printf("чиселки: %lf %lf %lf %lf\n", epsilon_t, side1, side2, side3);

            int result_t;
            enum Errors status_t = check_triangle(epsilon_t, side1, side2, side3, &result_t);
            if(status_t == OVERFLOW_ERROR)
            {
                printf("Ошибка: произошло переполение\n");
                return OVERFLOW_ERROR;
            }
            else if (status_t == INVALID_INPUT)
            {
                printf("Ошибка: некорректный ввод чисел\n");
                return INVALID_INPUT;
            }

            if(result_t == 1) printf("Стороны образуют прямоугольный треугольник\n");
            else printf("Стороны НЕ образуют прямоугольный треугольник\n");

            break;

        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            return INVALID_INPUT;
    }

    return 0;
}