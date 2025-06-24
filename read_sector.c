#include <stdio.h>
#include <stdint.h>

#define SECTOR_SIZE 512

int read_sector(int sector, void *buffer) {
    FILE *img = fopen("disk.img", "rb");
    if (!img) {
        perror("disk.img");
        return 0;
    }
    fseek(img, sector * SECTOR_SIZE, SEEK_SET);
    size_t read = fread(buffer, 1, SECTOR_SIZE, img);
    fclose(img);
    return read == SECTOR_SIZE;
}
