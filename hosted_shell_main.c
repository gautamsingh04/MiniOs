#include <stdio.h>
#include <string.h>
#include "fs.h"

void print(const char *str) {
    while (*str) putchar(*str++);
}

void get_input(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
    buffer[strcspn(buffer, "\r\n")] = 0;
}

void help() {
    printf("Supported commands:\n");
    printf("dir          - List files\n");
    printf("cat <file>   - Display file contents\n");
    printf("delete <file>- Remove a file (in memory)\n");
    printf("mkdir <dir>  - Create directory (in memory)\n");
    printf("write <file> - Write a new file\n");
    printf("save         - Save file table to disk\n");
    printf("help         - Show this message\n");
}

void shell() {
    char command[64];
    print("MiniOS Shell (hosted mode)\nType command:\n\n");

    while (1) {
        print("$ ");
        get_input(command, sizeof(command));

        if (command[0] == '\0') continue;
        if (strcmp(command, "dir") == 0) {
            list_dir();
        } else if (strncmp(command, "cat ", 4) == 0) {
            cat_file(command + 4);
        } else if (strncmp(command, "delete ", 7) == 0) {
            delete_file(command + 7);
        } else if (strncmp(command, "mkdir ", 6) == 0) {
            make_dir(command + 6);
        } else if (strncmp(command, "write ", 6) == 0) {
            write_file(command + 6);
        } else if (strcmp(command, "save") == 0) {
            save_file_table();
        } else if (strcmp(command, "help") == 0) {
            help();
        } else {
            print("Unknown command\n");
        }
    }
}

int main() {
    shell();
    return 0;
}
