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
    double a = 0.0, b = 1.0, previous_result = 0.0, result = 0.0;
    int n = 1;
    do {
        previous_result = result;
        result = rectangle_method(a, b, n, epsilon, integral_a);
        n *= 2;
    } while (fabs(result - previous_result) > epsilon);
    printf("a: %lf\n", result);

    a = 0.0, b = 1.0, previous_result = 0.0, result = 0.0, n = 1;
    do {
        previous_result = result;
        result = rectangle_method(a, b, n, epsilon, integral_b);
        n *= 2;
    } while (fabs(result - previous_result) > epsilon);
    printf("b: %lf\n", result);

    a = 0.0, b = 1.0, previous_result = 0.0, result = 0.0, n = 1;
    do {
        previous_result = result;
        result = rectangle_method(a, b, n, epsilon, integral_c);
        n *= 2;
    } while (fabs(result - previous_result) > epsilon);
    printf("c: %lf\n", result);

    a = 0.0, b = 1.0, previous_result = 0.0, result = 0.0, n = 1;
    do {
        previous_result = result;
        result = rectangle_method(a, b, n, epsilon, integral_d);
        n *= 2;
    } while (fabs(result - previous_result) > epsilon);
    printf("d: %lf\n", result);

    return 0;
}