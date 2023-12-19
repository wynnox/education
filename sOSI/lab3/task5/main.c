#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

enum errors
{
    OK,
    INVALID_INPUT
};

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <directory1> <directory2> ...\n", argv[0]);
        return INVALID_INPUT;
    }

    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char path[1025] = "\0";
    for(int i = 1; i < argc; ++i)
    {
        dir = opendir(argv[i]);
        if(dir == NULL)
        {
            printf("Failed to open directory: %s", argv[i]);
            continue;
        }

        printf("%s\n", argv[i]);

        while ((entry = readdir(dir)) != NULL)
        {
            snprintf(path, sizeof(path), "%s/%s", argv[i], entry->d_name);

            if (stat(path, &file_stat) == -1)
            {
                printf("\tError oppening file: %s\n", entry->d_name);
                continue;
            }


            printf("\t%s", entry->d_name);
            if (S_ISDIR(file_stat.st_mode))
            {
                printf("[directory]\n");
            } else if (S_ISREG(file_stat.st_mode))
            {
                printf("[file]\n");
            } else if (S_ISLNK(file_stat.st_mode))
            {
                printf("[symlink]\n");
            } else if (S_ISFIFO(file_stat.st_mode))
            {
                printf("[FIFO]\n");
            } else if (S_ISSOCK(file_stat.st_mode))
            {
                printf("[socket]\n");
            } else if (S_ISCHR(file_stat.st_mode))
            {
                printf("[character device]\n");
            } else if (S_ISBLK(file_stat.st_mode))
            {
                printf("[block device]\n");
            } else {
                printf("[unknown]\n");
            }
        }

        closedir(dir);
    }

    return 0;
}