#include "calculation.h"

int main()
{
    bool res;
    printf("\nTest 4.1\n\n");
//    Point points[4];

    Point p1 = (Point){0, 0};
    Point p2 = (Point){1, 0};
    Point p3 = (Point){1, 1};
    Point p4 = (Point){0, 1};
    printf("\ttest 1\n{{0,0}, {1, 0}, {1, 1}, {0, 1}}\nexpected result: yes\n");
    res = is_convex(4, p1, p2, p3, p4);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }

    p1 = (Point){0, 0};
    p2 = (Point){1, 0};
    p3 = (Point){0, 1};
    p4 = (Point){1, 1};
    printf("\ttest 2\n{{0,0}, {1, 0}, {0, 1}, {1, 1}}\nexpected result: no\n");
    res = is_convex(4, p1, p2, p3, p4);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }

    // Тест 3: многоугольник с тремя вершинами
    p1 = (Point){0, 0};
    p2 = (Point){1, 0};
    p3 = (Point){0, 1};
    printf("\ttest 3\n{{0,0}, {1, 0}, {0, 1}}\nexpected result: yes\n");
    res = is_convex(3, p1, p2, p3);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }

// Тест 4: многоугольник с двумя вершинами
    p1 = (Point){0, 0};
    p2 = (Point){1, 0};
    printf("\ttest 4\n{{0,0}, {1, 0}}\nexpected result: yes\n");
    res = is_convex(2, p1, p2);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }

// Тест 5: многоугольник с одной вершиной
    p1 = (Point){0, 0};
    printf("\ttest 5\n{{0,0}}\nexpected result: yes\n");
    res = is_convex(1, p1);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }

// Тест 6: пустой многоугольник
    printf("\ttest 6\n{}\nexpected result: yes\n");
    res = is_convex(0);
    if(res)
    {
        printf("\t\t result: yes\n");
    }
    else
    {
        printf("\t\t result: no\n");
    }


    double result;
    enum errors err;

    printf("\nTest 4.2\n\n");
    //тест 1
    printf("\ttest 1\n2x^2 + 3x + 4 at x = 1\nexpected result: 9\n");
    err = calculate_polynomial(&result, 1.0, 2, 2.0, 3.0, 4.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 2
    printf("\n\ttest 2\n1x^3 + 2x^2 + 3x + 4 at x = 2\nexpected result: 26\n");
    err = calculate_polynomial(&result, 2.0, 3, 1.0, 2.0, 3.0, 4.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 3
    printf("\n\ttest 3\n1x^4 + 2x^3 + 3x^2 + 4x + 5 at x = 2\nexpected result: 57\n");
    err = calculate_polynomial(&result, 2.0, 4, 1.0, 2.0, 3.0, 4.0, 5.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 4
    printf("\n\ttest 4\n1x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6 at x = 1\nexpected result: 21\n");
    err = calculate_polynomial(&result, 1.0, 5, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    if(err == OK)
    {
        printf("\t\t result: %f\n", result);
    }
    else
    {
        printf("error\n");
    }

    //тест 5
    printf("\n\ttest 5\nOverflow check\nexpected result: error\n");
    err = calculate_polynomial(&result, 1e307, 2, 1e307, 1e307, 1e307);
    if(err == OVERFLOW_ERROR)
    {
        printf("\t\t result: Overflow error\n");
    }
    else
    {
        printf("error\n");
    }

    return 0;
}