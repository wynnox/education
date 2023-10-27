#include "calculation.h"

/*
 *  Многоугольник является выпуклым, если z-компоненты векторного
 *  произведения всех пар ребер либо все положительные, либо все
 *  отрицательные. Если это условие не выполняется, многоугольник
 *  не является выпуклым.
 */

double crossProduct(Point first, Point second)
{
    return first.x * second.y - first.y * second.x;
}

bool is_convex(int count, ...)
{
    va_list args;
    va_start(args, count);

    int prev_sign = 0, curr_sign;
    Point first = va_arg(args, Point);
    Point second = va_arg(args, Point);
    prev_sign = crossProduct(first, second) > 0 ? 1 : 0;
    for(int i = 0; i < count - 2; ++i)
    {
        Point points = va_arg(args, Point);
        curr_sign = crossProduct(points, second) > 0 ? 1 : 0;
        if (curr_sign != 0 && curr_sign != prev_sign)
        {
            return false;
        }
        second = points;
    }

    curr_sign = crossProduct(second, first);
    if (curr_sign != 0 && curr_sign != prev_sign)
    {
        return false;
    }
    va_end(args);
    return true;
}

enum errors calculate_polynomial(double * result, double x, int n, ...)
{
    va_list args;
    va_start(args, n);

    *result = 0;
    for(int i = n; i >= 0; --i)
    {
        double coeff = va_arg(args, double);
        *result += coeff * pow(x, i);
        if(isinf(*result) || isnan(*result))
        {
            return OVERFLOW_ERROR;
        }
    }

    va_end(args);
    return OK;
}