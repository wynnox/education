#include "calculation.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("инвалидный инпут\n");
        return INVALID_INPUT;
    }
    double epsilon;
    if(convert_str_to_double(argv[1], &epsilon) != OK ||
        epsilon <= 0)
    {
        printf("некорректный epsilon\n");
        return INVALID_INPUT;
    }

    double results[15];
    results[0] = limit_e(epsilon);
    results[1] = limit_pi(epsilon);
    results[2] = limit_ln(epsilon);
    results[3] = limit_sqrt(epsilon);
    results[4] = limit_y(epsilon);

    results[5] = row_e(epsilon);
    results[6] = row_pi(epsilon);
    results[7] = row_ln(epsilon);
    results[8] = row_sqrt(epsilon);
    results[9] = row_y(epsilon);

    results[10] = equation_e(epsilon);
    results[11] = equation_pi(epsilon);
    results[12] = equation_ln(epsilon);
    results[13] = equation_sqrt(epsilon);
    results[14] = equation_y(epsilon);

    char* constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    char* ways[3] = {"LIMITS", "ROWS","EQUATIONS"};

    int precision = 0;
    double temp = epsilon;
    while (temp != 1)
    {
        temp *= 10;
        ++precision;
    }
    for(int i = 0; i < 15; i++){
        if(i%5 == 0){
            printf("\n %6c%s", ' ', ways[i/5]);
        }
        printf("\nresult for %s:", constants[i%5]);
        if (results[i] != INFINITY && !isnan(results[i])) {
            printf(" %.*f", precision, results[i]);
        } else {
            printf(" couldn't calculate constant with given accuracy");
        }
    }

    return 0;
}