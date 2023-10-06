#include "command_shell.h"

enum errors reading_users_from_file(FILE * input_file, User * user_data, int* count_users, int * capacity_user_data)
{
    *count_users = 0;
    //вообще не оч делаю, но как есть, считаю, что уже в файле всё валидно
    while(fscanf(input_file, "%6s%d%d", user_data[*count_users].login, &user_data[*count_users].pin, &user_data[*count_users].limit_request) == 3)
    {
        (*count_users)++;
        if(*count_users == *capacity_user_data)
        {
            //обычно стоит умножать на 2, но типо хз, пока так
            *capacity_user_data += 100;
            User * for_realloc = realloc(user_data, *capacity_user_data * sizeof(User));
            if(for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            user_data = for_realloc;
        }
    }
    return OK;
}

enum errors registration_or_authorization(FILE * output_file, User * user_data, int* count_users, int * capacity_user_data, int * index_user)
{
    printf("Добро пожаловать!\nСписок доступных команд:\n1 - авторизация\n2 - регистрация\nВведите нужное действие: ");
    int flag;
    //нужна проверка
    scanf("%d", &flag);
    char * buffer = (char *)malloc(11 * sizeof(char));
    if(buffer == 0)
    {
        printf("puppu\n");
        return INVALID_MEMORY;
    }
    int len_buff = 0;
    int password = -1;
    (*index_user) = -1;
    switch (flag)
    {
    case 1:
        printf("Введите имя пользователя: ");

        scanf("%10s", buffer);
        while(buffer[len_buff] != '\0')
        {
            char c = buffer[len_buff];
            if(isdigit(c) || isalpha(c))
            {
                len_buff++;
            }
            else
            {
                printf("Некорректный символ: %c\n", c);
                free(buffer);
                return INVALID_INPUT;
            }
            if(len_buff == 6)
            {
                printf("Длинное имя пользователя\n");
                free(buffer);
                return INVALID_INPUT;
            }
        }
        printf("Введенный пользователь: %s\n", buffer);

        for(int i = 0; i < *count_users; ++i)
        {
            if(!strcmp(user_data[i].login, buffer))
            {
                (*index_user) = i;
                break;
            }
        }
        if((*index_user) == -1)
        {
            printf("Такого пользователя нет\n");
            free(buffer);
            return INVALID_INPUT;
        }

        printf("Введите пароль: ");

        scanf("%d", &password);
        if(password < 0 || password > 100000)
        {
            printf("Некорректный пароль\n");
            free(buffer);
            return INVALID_INPUT;
        }
        if(user_data[(*index_user)].pin != password)
        {
            printf("Неверный пароль\n");
            free(buffer);
            return INVALID_INPUT;
        }
        printf("Вы успешно авторизировались\n");
        //можно вывести про количество ограничений
        break;
    case 2:
        printf("Введите имя пользователя: ");

        scanf("%10s", buffer);
        while(buffer[len_buff] != '\0')
        {
            char c = buffer[len_buff];
            if(isdigit(c) || isalpha(c))
            {
                len_buff++;
            }
            else
            {
                printf("Некорректный символ: %c\n", c);
                free(buffer);
                return INVALID_INPUT;
            }
            if(len_buff == 6)
            {
                printf("Длинное имя пользователя\n");
                free(buffer);
                return INVALID_INPUT;
            }
        }
        printf("Введенный пользователь: %s\n", buffer);

        if(*capacity_user_data == *count_users)
        {
            *capacity_user_data += 100;
            User * for_realloc = realloc(user_data, *capacity_user_data * sizeof(User));
            if(for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            user_data = for_realloc;
        }

        for(int i = 0; i < *count_users; ++i)
        {
            if(!strcmp(user_data[i].login, buffer))
            {
                (*index_user) = i;
                break;
            }
        }
        if((*index_user) != -1)
        {
            printf("Имя пользователя занято\n");
            free(buffer);
            return INVALID_INPUT;
        }
        strcpy(user_data[*count_users].login, buffer);
        fprintf(output_file, "%s\n", buffer);

        printf("Введите пароль: ");

        scanf("%d", &password);
        if(password < 0 || password > 100000)
        {
            printf("Некорректный пароль\n");
            free(buffer);
            return INVALID_INPUT;
        }
        user_data[*count_users].pin = password;
        fprintf(output_file,"%d\n", password);

        user_data[*count_users].limit_request = 0;
        fprintf(output_file,"%d\n", 0);

        (*count_users)++;
        printf("Вы успешно зарегестрированы\n");
        break;
    default:
        printf("нет такой команды\n");
    }
    free(buffer);
    return OK;
}