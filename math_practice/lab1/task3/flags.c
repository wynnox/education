#include "math_calc_with_flags.h"

enum Errors convert_str_to_double (const char *str, double * result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0' || (*result == 0 && errno == ERANGE))
    {
        return INVALID_INPUT;
    }
    return OK;
}

enum Errors convert_str_to_int (const char *str, long int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

int check_overflow_double(double* num, double epsilon)
{
    return fabs(*num - fabs(DBL_MAX / *num)) > epsilon;
}

enum Errors check_triangle(double epsilon, double side1, double side2, double side3, int * result)
{
    if(!check_overflow_double(&side1, epsilon) || !check_overflow_double(&side2, epsilon) || !check_overflow_double(&side3, epsilon))
        return OVERFLOW_ERROR;

    if (side1 <= epsilon || side2 <= epsilon || side3 <= epsilon)
        return INVALID_INPUT;

    if(fabs(side1 * side1 + side2 * side2 - side3 * side3) <= epsilon ||
       fabs(side1 * side1 + side3 * side3 - side2 * side2) <= epsilon ||
       fabs(side2 * side2 + side3 * side3 - side1 * side1) <= epsilon)
        *result = 1;
    else
        *result = 0;

    return OK;

}

