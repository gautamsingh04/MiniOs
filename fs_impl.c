#include <stdio.h>
#include <string.h>
#include "fs.h"

struct FileEntry file_table_buffer[MAX_FILES];
int table_loaded = 0;

void load_file_table() {
    if (!table_loaded) {
        read_sector(DIR_SECTOR, file_table_buffer);
        table_loaded = 1;
    }
}

void save_file_table() {
    FILE *img = fopen("disk.img", "r+b");
    if (!img) {
        perror("save_file_table: disk.img");
        return;
    }
    fseek(img, DIR_SECTOR * 512, SEEK_SET);
    fwrite(file_table_buffer, sizeof(struct FileEntry), MAX_FILES, img);
    fclose(img);
}

void list_dir() {
    load_file_table();
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table_buffer[i].name[0] == 0) continue;
        printf("%-12s [%s]\n",
            file_table_buffer[i].name,
            file_table_buffer[i].type == FILETYPE_DIR ? "DIR" : "FILE");
    }
}

void cat_file(char *name) {
    load_file_table();
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(file_table_buffer[i].name, name) == 0) {
            uint16_t size = file_table_buffer[i].size_sec;
            uint16_t start = file_table_buffer[i].start_sec;
            uint32_t total_bytes = size * 512;
            char buffer[512 * 8 + 1] = {0};

            if (size > 8) {
                printf("File too large to display (max 8 sectors)\n");
                return;
            }

            FILE *img = fopen("disk.img", "rb");
            if (!img) {
                perror("disk.img");
                return;
            }
            fseek(img, start * 512, SEEK_SET);
            size_t read = fread(buffer, 1, total_bytes, img);
            fclose(img);

            if (read != total_bytes) {
                printf("Failed to read full file content\n");
                return;
            }

            for (size_t j = 0; j < read; j++) {
                putchar(buffer[j]);
            }
            putchar('\n');
            return;
        }
    }
    printf("File not found\n");
}

void delete_file(char *name) {
    load_file_table();
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(file_table_buffer[i].name, name) == 0) {
            file_table_buffer[i].name[0] = 0;
            printf("File deleted (in memory only)\n");
            return;
        }
    }
    printf("File not found\n");
}

void make_dir(char *name) {
    load_file_table();
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table_buffer[i].name[0] == 0) {
            strncpy(file_table_buffer[i].name, name, 12);
            file_table_buffer[i].type = FILETYPE_DIR;
            file_table_buffer[i].start_sec = 0;
            file_table_buffer[i].size_sec = 0;
            printf("Directory created (in memory only)\n");
            return;
        }
    }
    printf("No space for new directory\n");
}

void write_file(char *name) {
    load_file_table();
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table_buffer[i].name[0] == 0) {
            printf("Enter file content (end with ~ on a new line):\n");
            char content[1024] = {0};
            char line[256];
            while (fgets(line, sizeof(line), stdin)) {
                if (line[0] == '~') break;
                strcat(content, line);
            }

            int start_sector = 10 + i;
            int size_sec = (strlen(content) + 511) / 512;

            FILE *img = fopen("disk.img", "r+b");
            if (!img) return;
            fseek(img, start_sector * 512, SEEK_SET);
            fwrite(content, 1, size_sec * 512, img);
            fclose(img);

            strncpy(file_table_buffer[i].name, name, 12);
            file_table_buffer[i].type = FILETYPE_FILE;
            file_table_buffer[i].start_sec = start_sector;
            file_table_buffer[i].size_sec = size_sec;
            printf("File written to disk (not saved to table yet)\n");
            return;
        }
    }
    printf("No space left for new file\n");
}
