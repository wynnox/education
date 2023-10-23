#include "calculation.h"

/*
 *  Многоугольник является выпуклым, если z-компоненты векторного
 *  произведения всех пар ребер либо все положительные, либо все
 *  отрицательные. Если это условие не выполняется, многоугольник
 *  не является выпуклым.
 */
//bool is_convex(int count, ...)
//{
//    va_list args;
//    va_start(args, count);
//
//    double z;
//    double dx1, dy1, dx2, dy2;
//    int prev_sign = 0, curr_sign;
//    for(int i = 0; i < count; ++i)
//    {
//        Point points = va_arg(args, Point);
//
//    }
//
//    va_end(args);
//    return true;
//}

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