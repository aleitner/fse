#include "fse/save_dat_header.h"

#include <arpa/inet.h>

void read_header(FILE *file, save_dat_header_t *header) {
    // Read the save_dat_header_t structure from the file.
    fseek(file, 0, SEEK_SET);
    fread(header, sizeof(save_dat_header_t), 1, file);
}

void print_header(const save_dat_header_t *header) {
    // Convert game_version to a readable format and ensure strings are null-terminated.
    char game_version_str[SIZE_VERSION * 3]; // x.x format
    sprintf(game_version_str, "%d.%d%d", 
            header->game_version[1], header->game_version[2], header->game_version[3]);

    // Print the data.
    printf("Save File Signature: %s\n", header->save_file_signature);
    printf("Game Version: %s\n", game_version_str);
    printf("Letter 'R': %c\n", header->letter_r);
    printf("Player Name: %s\n", header->player_name);
    printf("Save Game Name: %s\n", header->savegame_name);
    printf("Saved Date (Realtime): %u-%u-%u\n", 
            ntohs(header->saved_day_realtime), ntohs(header->saved_month_realtime), 
            ntohs(header->saved_year_realtime));
    printf("Saved Date (In-game): %u-%u-%u\n", 
            ntohs(header->ingame_month), ntohs(header->ingame_day), ntohs(header->ingame_year));
    printf("In-game Date Ticks: %u\n", ntohs(header->ingame_date_ticks));
    printf("Current Map Number: %u\n", ntohs(header->map_number));
    printf("Current Map Level: %u\n", ntohs(header->map_level));
    printf("Current Map Filename: %s\n", header->current_map_filename);
}