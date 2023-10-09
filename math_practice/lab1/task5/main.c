#include "calculation_of_summ.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Ошибка: некорректный ввод\n");
        return INVALID_INPUT;
    }

    double x;
    double epsilon;

    if (convert_str_to_double(argv[1], &x) != OK ||
        convert_str_to_double(argv[2], &epsilon) != OK ||
        epsilon <= 0)
    {
        printf("Ошибка: введено некорректное число\n");
        return INVALID_INPUT;
    }

    double result_a = 0, result_b, result_c, result_d;

    taylor_a(x, epsilon, &result_a);
    printf("A: %lf\n", result_a);

    taylor_b(x, epsilon, &result_b);
    printf("B: %lf\n", result_b);

    if(fabs(x) < 1)
    {
        taylor_c(x, epsilon, &result_c);
        printf("C: %lf\n", result_c);

        taylor_d(x, epsilon, &result_d);
        printf("D: %lf\n", result_d);
    }
    else
    {
        printf("x должен быть в интервале (-1;1)\n");
        printf("x должен быть в интервале (-1;1)\n");
    }

    return 0;
}