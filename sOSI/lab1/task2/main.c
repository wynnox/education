#include "command_shell.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
         printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
         return INVALID_INPUT;
    }

    FILE * user_data_file = fopen(argv[1], "r+");
    if(user_data_file == NULL)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        return ERROR_OPEN_FILE;
    }

    int count_users = 0;
    int capacity_user_data = 100;
    User * user_data = (User*)malloc(capacity_user_data * sizeof(User));
    if(user_data == NULL)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        if(user_data_file != NULL) fclose(user_data_file);
        return ERROR_OPEN_FILE;
    }

    if (reading_users_from_file(user_data_file, user_data,
                                &count_users, &capacity_user_data) != OK)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        if(user_data_file != NULL) fclose(user_data_file);
        free(user_data);
        return ERROR_OPEN_FILE;
    }


    int index_user = -1;
    if(registration_or_authorization(user_data_file, user_data,
                                     &count_users, &capacity_user_data,
                                     &index_user) != OK)
    {
        if(user_data_file != NULL) fclose(user_data_file);
        free(user_data);
        return INVALID_INPUT;
    }

    command();

    int count_limit = 1;
    char * command_user = (char *)malloc((MAX_SIZE + 1) * sizeof(char));
    if(command_user == NULL)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        if(user_data_file != NULL) fclose(user_data_file);
        free(user_data);
        return INVALID_MEMORY;
    }
    char * buffer = (char *)malloc((MAX_SIZE + 1) * sizeof(char));
    if(buffer == NULL)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        if(user_data_file != NULL) fclose(user_data_file);
        free(user_data);
        free(command_user);
        return INVALID_MEMORY;
    }

    while (1)
    {
        printf("%s@nncl:~$ ", user_data[index_user].login);
        if(user_data[index_user].limit_request == count_limit)
        {
            break;
        }
        scanf("%20s", command_user);
        if(strcmp(command_user, "Time") == 0)
        {
            time_t mytime = time(NULL);
            // если вернулось -1 то время недоступно
            struct tm *now = localtime(&mytime);
            printf("%s@nncl:~$ %02d:%02d:%02d\n", user_data[index_user].login, now->tm_hour, now->tm_min, now->tm_sec);
        }
        else if (strcmp(command_user, "Date") == 0)
        {
            time_t mytime = time(NULL);
            struct tm *now = localtime(&mytime);
            printf("%s@nncl:~$ %02d.%02d.%d\n", user_data[index_user].login, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
        }
        else if(strcmp(command_user, "Howmuch") == 0)
        {
            int day = -1, month = -1, year = -1;
            char flag = 0;
            if (scanf("%d.%d.%d -%c", &day, &month, &year, &flag) != 4)
            {
                printf("%s@nncl:~$ некорректная дата\n", user_data[index_user].login);
                break;
            }
            if(day < 0 && month < 0 && year < 0)
            {
                printf("%s@nncl:~$ некорректная дата\n", user_data[index_user].login);
                break;
            }

            time_t mytime = time(NULL);
            struct tm *now = localtime(&mytime);
            now->tm_mon += 1;
            now->tm_year += 1900;
            struct tm user_date = {0};
            user_date.tm_mday = day;
            user_date.tm_mon = month - 1;
            user_date.tm_year = year - 1900;
            time_t user_time = mktime(&user_date);


            double diff_second = difftime(mytime, user_time);
            double diff_time;
            //проверить на положительное значение, потому что да
            switch (flag)
            {
                case 's':
                    diff_time = diff_second;
                    printf("Elapsed time: %.0lf\n", diff_time);
                    break;
                case 'm':
                    diff_time = diff_second / 60;
                    printf("Elapsed time: %.0lf\n", diff_time);
                    break;
                case 'h':
                    diff_time = diff_second / 3600;
                    printf("Elapsed time: %.0lf\n", diff_time);
                    break;
                case 'y':
                    diff_time = diff_second / (3600 * 24 * 365.25);
                    printf("Elapsed time: %.0lf\n", diff_time);
                    break;
                default:
                    printf("%s@nncl:~$ некорректный флаг\n", user_data[index_user].login);
                    break;
            }
        }
        else if(strcmp(command_user, "Logout") == 0)
        {
            if(registration_or_authorization(user_data_file, user_data,
                                             &count_users, &capacity_user_data,
                                             &index_user) != OK)
            {
                if(user_data_file != NULL) fclose(user_data_file);
                free(user_data);
                free(command_user);
                free(buffer);
                return INVALID_INPUT;
            }
            count_limit = 1;
        }
        else if(strcmp(command_user, "Sanctions") == 0)
        {
            if(scanf("%20s", buffer) != 1)
            {
                printf("%s@nncl:~$ некорректный ввод\n", user_data[index_user].login);

            }
            int temp_index = -1;
            for(int i = 0; i < count_users; ++i)
            {
                if(!strcmp(user_data[i].login, buffer))
                {
                    temp_index = i;
                    break;
                }
            }
            if(temp_index == -1)
            {
                printf("%s@nncl:~$ пользователя %s нет\n", user_data[index_user].login, buffer);
                break;
            }



        }
        else if(strcmp(command_user, "Exit") == 0)
        {
            break;
        }
        else
        {
            printf("такой команды нет\n");
        }
        count_limit++;
    }

    if(user_data[index_user].limit_request == count_limit)
    {
        printf("Достигнут лимит запросов\n");
    }

    if(user_data_file != NULL) fclose(user_data_file);
    free(user_data);
    free(command_user);
    free(buffer);
    return 0;
}
