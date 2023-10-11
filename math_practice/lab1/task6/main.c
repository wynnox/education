#include "calculation.h"

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Ошибка: инвалидный инпут");
        return INVALID_INPUT;
    }
    double epsilon;

    if  (convert_str_to_double(argv[1], &epsilon) != OK ||
        epsilon <= 0)
    {
        printf("Ошибка: инвалидный инпут");
        return INVALID_INPUT;
    }

    double result_a = integral(epsilon, integral_a);
    printf("a: %lf\n", result_a);

    double result_b = integral(epsilon, integral_b);
    printf("b: %lf\n", result_b);

    double result_c = integral(epsilon, integral_c);
    printf("c: %lf\n", result_c);

    double result_d = integral(epsilon, integral_d);
    printf("d: %lf\n", result_d);

    return 0;
}