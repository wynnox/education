(Таненбаум, Гл. 4, задание 46) Реализуйте собственную версию программы ls. Ваша
версия должна принимать в качестве аргумента одно или несколько имен каталогов и
для каждого каталога выдавать список всех файлов, содержащихся в этом каталоге, по
одной строке на каждый файл. При выводе каждое поле должно форматироваться в
соответствии с его типом. Для каждого файла укажите в списке только первый
дисковый адрес файла.

```c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_SIZE 512

typedef enum status_code {
    code_success,
    code_invalid_parameter,
    code_error_directory,
    code_file_error
} status_code;

status_code print_in_file(const char* path, const char* filename) {
    if (!filename || !path) return code_invalid_parameter;
    struct stat buff;
    int check = stat(path, &buff);
    if (check == -1) {
        return code_file_error;
    }
    printf("    %s", filename);
    if (S_ISDIR(buff.st_mode)) {
        printf("[directory]\n");
    } else if (S_ISREG(buff.st_mode)) {
        printf("[file]\n");
    } else if (S_ISLNK(buff.st_mode)) {
        printf("[symlink]\n");
    } else if (S_ISFIFO(buff.st_mode)) {
        printf("[FIFO]\n");
    } else if (S_ISSOCK(buff.st_mode)) {
        printf("[socket]\n");
    } else if (S_ISCHR(buff.st_mode)) {
        printf("[character device]\n");
    } else if (S_ISBLK(buff.st_mode)) {
        printf("[block device]\n");
    } else {
        printf("[unknown]\n");
    }
    return code_success;
}

status_code my_ls(const char* path) {
    struct dirent* entry;
    DIR* dir = opendir(path);
    status_code st_act;
    if (dir == NULL) return code_error_directory;

    printf("%s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[MAX_SIZE];
        struct stat statbuf;
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        st_act = print_in_file(fullpath, entry->d_name);
        if (st_act != code_success) {
            closedir(dir);
            return code_file_error;
        }
    }
    closedir(dir);
    return code_success;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid parameter detected!!!\n");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        status_code st_act = my_ls(argv[i]);
        switch (st_act) {
            case code_invalid_parameter:
                printf("Invalid parameter detected!!!\n");
                break;
            case code_error_directory:
                printf("Error oppening directory detected!!!\n");
                break;
            case code_file_error:
                printf("Error oppening file detected!!!\n");
                break;
            default:
                break;
        }
    }

    return 0;
}
```