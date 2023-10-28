#include "overbullshit.h"

//Это число получается из максимального числа 3888,
// которое в римской системе счисления представляется как
// "MMMDCCCLXXXVIII". Эта строка содержит 15 символов.
char * Ro(int num)
{
    if(num > 3999 || num < 1)
    {
        return NULL;
    }

    char* roman = (char *)malloc(sizeof(char) * 16);
    if (roman == NULL)
    {
        return NULL;
    }

    roman[0] = '\0';

    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < 13; i++)
    {
        while (num >= values[i])
        {
            strcat(roman, symbols[i]);
            num -= values[i];
        }
    }

    return roman;
}

//char * Zr(int num, int base)
//{
//
//}