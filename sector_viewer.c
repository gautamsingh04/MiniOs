#include <stdio.h>
#include <stdint.h>

#define SECTOR_SIZE 512
#define MAX_SECTORS 9  
int read_sector(int sector, void *buffer);

void print_sector_hex(int sector) {
    uint8_t buffer[SECTOR_SIZE];
    if (!read_sector(sector, buffer)) {
        printf("Failed to read sector %d\n", sector);
        return;
    }

    printf("\n📦 Sector %d (offset %d):\n", sector, sector * SECTOR_SIZE);
    for (int i = 0; i < SECTOR_SIZE; i += 16) {
        printf("%04X  ", i);
        for (int j = 0; j < 16; j++) {
            printf("%02X ", buffer[i + j]);
        }
        printf(" ");
        for (int j = 0; j < 16; j++) {
            char c = buffer[i + j];
            printf("%c", (c >= 32 && c < 127) ? c : '.');
        }
        printf("\n");
    }
}

int main() {
    for (int i = 0; i < MAX_SECTORS; i++) {
        print_sector_hex(i);
    }
    return 0;
}
