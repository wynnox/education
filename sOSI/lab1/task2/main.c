#include "command_shell.h"

/*
 * 1) файл с данными юзера, сюда надо добавлять при регистрации
 * и при запуске выгружать
 * 2) файл с приветствием и доступными командами
 * 3) возможно тут будет файл с логами, хз насколько надо это надо
 */

int main(int argc, char* argv[])
{
     if (argc != 3)
     {
         printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
         return INVALID_INPUT;
     }

     FILE * user_data_file = fopen(argv[1], "r+");
     FILE * command_file = fopen(argv[2], "r");
     if(user_data_file == NULL || command_file == NULL)
     {
         printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
         if(user_data_file != NULL) fclose(user_data_file);
         if(command_file != NULL) fclose(command_file);
         return ERROR_OPEN_FILE;
     }

     int count_users = 0;
     int capacity_user_data = 100;
     User * user_data = (User*)malloc(capacity_user_data * sizeof(User));
     if(user_data == NULL)
     {
         printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
         if(user_data_file != NULL) fclose(user_data_file);
         if(command_file != NULL) fclose(command_file);
         return ERROR_OPEN_FILE;
     }

    if (reading_users_from_file(user_data_file, user_data, &count_users, &capacity_user_data) != OK)
    {
        printf("Произошла ошибка, повторите ошибку позже или обратитесь к админитратору\n");
        if(user_data_file != NULL) fclose(user_data_file);
        if(command_file != NULL) fclose(command_file);
        free(user_data);
        return ERROR_OPEN_FILE;
    }

    printf("ПРОВЕРКА:\nпользователи:\n");
    for(int i = 0; i < count_users; ++i)
    {
        printf("login:%s pin:%d limit:%d\n", user_data[i].login, user_data[i].pin, user_data[i].limit_request);
    }

    int index_user = -1;
    registration_or_authorization(user_data_file, user_data, &count_users, &capacity_user_data, &index_user);

//    for(int i = 0; i < count_users; ++i)
//    {
//        printf("login:%s pin:%d limit:%d\n", user_data[i].login, user_data[i].pin, user_data[i].limit_request);
//    }

    if(user_data_file != NULL) fclose(user_data_file);
    if(command_file != NULL) fclose(command_file);
    free(user_data);

    return 0;
}
