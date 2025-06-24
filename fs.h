#ifndef FS_H
#define FS_H

#include <stdint.h>

#define DIR_SECTOR 4
#define MAX_FILES  30
#define FILETYPE_FILE 0
#define FILETYPE_DIR  1

struct FileEntry {
    char name[12];
    uint8_t type;
    uint16_t start_sec;
    uint16_t size_sec;
};

extern struct FileEntry file_table_buffer[MAX_FILES];

void load_file_table();
void save_file_table();
void list_dir();
void cat_file(char *name);
void delete_file(char *name);
void make_dir(char *name);
void write_file(char *name);
int read_sector(int sector, void *buffer);  

#endif
