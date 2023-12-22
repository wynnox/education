#include "overbullshit.h"

int oversprintf(char * str, const char * format, ...)
{
    if(str == NULL || format == NULL)
    {
        return -1;
    }

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
            char * res = Ro(num);
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'Z' && format[i+2] == 'r')
        {
            unsigned int num = va_arg(args, unsigned int);
            char * res = Zeckendorf(num);
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i+=2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'v')
        {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char * array_base = "0123456789abcdefghijklmnopqrstuvwxyz";
            char * res = Cv(num, base, array_base);
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if (format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'V')
        {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char * array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            char * res = Cv(num, base, array_base);
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 't' && format[i+2] == 'o') {
            char *number = va_arg(args,
            char *);
            int base = va_arg(args,
            int);
            if (number[0] == '\0') {
                i += 2;
                continue;
            }

            if (base < 2 || base > 36) base = 10;

            for (size_t i = 0; i < strlen(number); ++i) {
                if (!isdigit(number[i]) && !(number[i] >= 'a' && number[i] <= 'z')) {
                    i += 2;
                    continue;
                }

            }
            int number_int;
            enum errors err = To(number, base, &number_int);
            if (err != OK) {
                i += 2;
                continue;
            }
            char buffer[50];
            sprintf(str + count, "%d", number_int);
            count += strlen(buffer);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'T' && format[i+2] == 'O')
        {
            char * number = va_arg(args, char *);
            int base = va_arg(args, int);
            if(number[0] == '\0')
            {
                i+=2;
                continue;
            }

            if(base < 2 || base > 36) base = 10;

            for(size_t i = 0; i < strlen(number); ++i)
            {
                if(!isdigit(number[i]) && !(number[i] >= 'A' && number[i] <= 'Z'))
                {
                    i += 2;
                    continue;
                }

            }
            int number_int;
            enum errors err = To(number, base, &number_int);
            if(err != OK)
            {
                i+=2;
                continue;
            }
            char buffer[50];
            sprintf(str + count, "%d", number_int);
            count += strlen(buffer);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'i')
        {
            int n = va_arg(args, int);
            char * res = dump_memory(&n, sizeof(int));
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'u')
        {
            unsigned int n = va_arg(args, unsigned int);
            char * res = dump_memory(&n, sizeof(unsigned int));
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'd')
        {
            double n = va_arg(args, double );
            char * res = dump_memory(&n, sizeof(double ));
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'f')
        {
            double n = va_arg(args, double);
            char * res = dump_memory(&n, sizeof(float));
            if(res != NULL)
            {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 1 && format[i + 1] == 'n')
        {
            int * k = va_arg(args, int *);
            *k = count;
            i += 1;
        }
        else if(format[i] == '%')
        {
            char * symbols = "diouxXeEfFgGaAcspn%";
            char * end_type = strpbrk(format + i, symbols);
            int diff = end_type - format;
            char * mini_format = (char*)malloc(sizeof(char) * (diff + 1));
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

int overfprintf(FILE* stream, char* format, ...)
{
    if(stream == NULL || format == NULL)
    {
        return -1;
    }

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
            char * res = Ro(num);
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'Z' && format[i+2] == 'r')
        {
            unsigned int num = va_arg(args, unsigned int);
            char * res = Zeckendorf(num);
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i+=2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'v')
        {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char * array_base = "0123456789abcdefghijklmnopqrstuvwxyz";
            char * res = Cv(num, base, array_base);
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if (format[i] == '%' && i < len_format - 2 && format[i+1] == 'C' && format[i+2] == 'V')
        {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char * array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            char * res = Cv(num, base, array_base);
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 't' && format[i+2] == 'o') {
            char *number = va_arg(args,
            char *);
            int base = va_arg(args,
            int);
            if (number[0] == '\0') {
                i += 2;
                continue;
            }

            if (base < 2 || base > 36) base = 10;

            for (size_t i = 0; i < strlen(number); ++i) {
                if (!isdigit(number[i]) && !(number[i] >= 'a' && number[i] <= 'z')) {
                    i += 2;
                    continue;
                }

            }
            int number_int;
            enum errors err = To(number, base, &number_int);
            if (err != OK) {
                i += 2;
                continue;
            }
            char buffer[50];
            fprintf(stream, "%d", number_int);
            count += strlen(buffer);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'T' && format[i+2] == 'O')
        {
            char * number = va_arg(args, char *);
            int base = va_arg(args, int);
            if(number[0] == '\0')
            {
                i+=2;
                continue;
            }

            if(base < 2 || base > 36) base = 10;

            for(size_t i = 0; i < strlen(number); ++i)
            {
                if(!isdigit(number[i]) && !(number[i] >= 'A' && number[i] <= 'Z'))
                {
                    i += 2;
                    continue;
                }

            }
            int number_int;
            enum errors err = To(number, base, &number_int);
            if(err != OK)
            {
                i+=2;
                continue;
            }
            char buffer[50];
            fprintf(stream, "%d", number_int);
            count += strlen(buffer);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'i')
        {
            int n = va_arg(args, int);
            char * res = dump_memory(&n, sizeof(int));
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'u')
        {
            unsigned int n = va_arg(args, unsigned int);
            char * res = dump_memory(&n, sizeof(unsigned int));
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'd')
        {
            double n = va_arg(args, double );
            char * res = dump_memory(&n, sizeof(double ));
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%' && i < len_format - 2 && format[i+1] == 'm' && format[i+2] == 'f')
        {
            double n = va_arg(args, double);
            char * res = dump_memory(&n, sizeof(float));
            if(res != NULL)
            {
                fputs(res, stream);
                count += strlen(res);
            }
            free(res);
            i += 2;
        }
        else if(format[i] == '%')
        {
            char * symbols = "diouxXeEfFgGaAcspn%";
            char * end_type = strpbrk(format + i, symbols);
            int diff = end_type - format;
            char * mini_format = (char*)malloc(sizeof(char) * (diff + 1));
            if(mini_format == NULL)
            {
                count = -2;
                va_end(args);
                return count;
            }
            memcpy(mini_format, format + i, diff);
            mini_format[diff] = '\0';
            int k = fprintf(stream, mini_format, args);
            if (k == -1)
            {
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
            fputc(format[i], stream);
            count++;
        }
    }

    va_end(args);
    return count;
}