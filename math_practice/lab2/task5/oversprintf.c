#include "overbullshit.h"

//Функция sprintf возвращает число байтов, сохраненное в буфере, не считая символ завершающего нуля.
int oversprintf(char * str, const char * format, ...)
{
    if(str == NULL || format == NULL)
    {
        return -1;
    }

    //ИЗ-ЗВ БЛЯТЬ STRCAT ЭТО ПИЗДА
    str[0] = '\0';
    int count = 0;
    int len_format = strlen(format);

    va_list args;
    va_start(args, format);

    for(int i = 0; i < len_format; ++i)
    {
        if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'R' && format[i+2] == 'o')
        {
            i += 2;
            int num = va_arg(args, int);
            //мб стоит перенести проверку числа сюда
            char * res = Ro(num);
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'Z' && format[i+2] == 'r')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'v')
//        {
//            int num = va_arg(args, int);
//            int base = va_arg(args, int);
//            if(base > 36 || base < 2)
//            {
//                base = 10;
//            }
//        }
//        else if (format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'V')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 't' && format[i+2] == 'o')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'T' && format[i+2] == 'O')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'i')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'u')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'd')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'f')
//        {
//            //
//        }
//        else if(format[i] == '%' && i < len_format - 1)
//        {
//            //
//        }
        else if(format[i] == '%')
        {
            char * symbols = "diouxXeEfFgGaAcspn%";
            char * end_type = strpbrk(format + i, symbols);
            int diff = end_type - format;
            char * mini_format = (char*)malloc(sizeof(char) * (diff + 1));
            //хуйня из под коня но оставим так
            if(mini_format == NULL)
            {
                str[count] = '\0';
                count = -2;
                va_end(args);
                return count;
            }
            memcpy(mini_format, format + i, diff);
            mini_format[diff] = '\0';
            int k = vsprintf(str + count, mini_format, args);
            printf("%s %d\n", mini_format, k);
            if (k == -1)
            {
                str[count] = '\0';
                count = -1;
                va_end(args);
                free(mini_format);
                return count;
            }
            i += (diff - 1);
            count += k;
            free(mini_format);
        }
        else
        {
            str[count++] = format[i];
        }
    }

    str[count] = '\0';
    va_end(args);
    return count;
}