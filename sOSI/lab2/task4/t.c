#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_LINE_LENGTH 256

void search_string_in_file(char *filename, char *search_string) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_string)) {
            printf("String found in file: %s\n", filename);
            break;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <list_file> <search_string>\n", argv[0]);
        return 1;
    }

    char *list_file = argv[1];
    char *search_string = argv[2];

    FILE *file = fopen(list_file, "r");
    if (file == NULL) {
        perror("Error opening list file");
        return 1;
    }

    char filename[MAX_FILENAME_LENGTH];
    int found = 0;
    while (fgets(filename, sizeof(filename), file)) {
        strtok(filename, "\n");  // Remove trailing newline character

        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking process");
            return 1;
        } else if (pid == 0) {  // Child process
            search_string_in_file(filename, search_string);
            exit(0);
        }
    }

    int status;
    while (wait(&status) > 0);  // Wait for all child processes to finish

    if (!found) {
        printf("String not found in any file\n");
    }

    fclose(file);
    return 0;
}
