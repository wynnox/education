#include "command_shell.h"

enum errors reading_users_from_file(FILE * input_file, User * user_data, int* count_users, int * capacity_user_data)
{
    *count_users = 0;
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
    if(*count_users == 0) return EMPTY_FILE;
    return OK;
}

enum errors registration_or_authorization(FILE * output_file, User * user_data, int* count_users, int * capacity_user_data, int * index_user, int * flag_empty_file)
{
    int flag;
    if(*flag_empty_file == EMPTY_FILE)
    {
        printf("Добро пожаловать!\nСписок доступных команд:\n2 - регистрация\nВведите нужное действие: ");
        scanf("%d", &flag);
        if(flag != 2)
        {
            printf("нет такой команды\n");
            return INVALID_INPUT;
        }
    }
    else
    {
        printf("Добро пожаловать!\nСписок доступных команд:\n1 - авторизация\n2 - регистрация\nВведите нужное действие: ");
        scanf("%d", &flag);
    }
    char * buffer = (char *)malloc(11 * sizeof(char));
    if(buffer == NULL)
    {
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
            if(user_data[*index_user].limit_request != 0)
            {
                printf("Для этого пользователя присутствует лимит команд: %d\n", user_data[*index_user].limit_request);
            }
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

            if (scanf("%d", &password) != 1)
            {
                printf("Некорректный пароль\n");
                free(buffer);
                return INVALID_INPUT;
            }
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

            *index_user = *count_users;
            (*count_users)++;

            printf("Вы успешно зарегестрированы\n");
            break;
        default:
            printf("нет такой команды\n");
            return INVALID_INPUT;
    }
    *flag_empty_file = OK;
    free(buffer);
    return OK;
}

void command()
{
    printf("Доступные комманды:\n"
           "1) Time - запрос текущего времени в стандартном формате чч:мм:сс;\n"
           "2) Date - запрос текущей даты в стандартном формате дд:мм:гггг;\n"
           "3) Howmuch <time> flag - запрос прошедшего времени с указанной даты в\n"
           "параметре <time>, параметр flag определяет тип представления результата\n"
           "(-s в секундах, -m в минутах, -h в часах, -y в годах)\n"
           "4) Logout - выйти в меню авторизации\n"
           "5) Sanctions username <number> - команда позволяет ввести ограничения на работу\n"
           "с оболочкой для пользователя username, а именно данный пользователь не может\n"
           "в одном сеансе выполнить более <number> запросов. Для подтверждения\n"
           "ограничений после ввода команды необходимо ввести значение 12345.\n"
           "6) Exit - выход из интрепретатора командной строки\n");
}

void writing_users_in_file(FILE * input_file, User * user_data, int* count_users)
{
    for(int i = 0; i < *count_users; ++i)
    {
        fprintf(input_file,"%s\n", user_data[i].login);
        fprintf(input_file,"%d\n", user_data[i].pin);
        fprintf(input_file, "%d\n", user_data[i].limit_request);
    }
}