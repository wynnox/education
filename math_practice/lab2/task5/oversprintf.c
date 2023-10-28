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
        //надо обработать случай когда нет после % % или спецификатора
        else if(format[i] == '%')
        {
            continue;
            //для одного % ничо не знаю, эт ошибка
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