#include "fse/header.h"

#include <arpa/inet.h>
#include <stdlib.h>

header_t* load_header(FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Invalid file pointer.\n");
        return NULL;
    }

    // Allocate memory for the header
    header_t *header = malloc(sizeof(header_t));
    if (header == NULL) {
        fprintf(stderr, "Memory allocation for header_t failed.\n");
        return NULL;
    }
    
    // Move the file pointer to the start of the file
    fseek(file, 0, SEEK_SET);

    // Read the header_t structure from the file into the allocated structure
    size_t num_read = fread(header, sizeof(header_t), 1, file);

    // Verify that fread successfully read 1 element
    if (num_read != 1) {
        fprintf(stderr, "Failed to read header_t from file.\n");
        free(header);
        return NULL;
    }

    return header;
}

void print_header(const header_t *header) {
    // Print the data.
    printf("Save File Signature: %s\n", header->save_file_signature);
    printf("Game Version: %d.%d%d\n", header->game_version[1], header->game_version[2], header->game_version[3]);
    printf("Letter 'R': %c\n", header->letter_r);
    printf("Player Name: %s\n", header->player_name);
    printf("Save Game Name: %s\n", header->savegame_name);
    printf("Saved Date (Realtime): %u-%u-%u\n", 
            ntohs(header->saved_day_realtime), ntohs(header->saved_month_realtime), 
            ntohs(header->saved_year_realtime));
    printf("Saved Date (In-game): %u-%u-%u\n", 
            ntohs(header->ingame_month), ntohs(header->ingame_day), ntohs(header->ingame_year));
    printf("In-game Date Ticks: %u\n", ntohl(header->ingame_date_ticks));
    printf("Current Map Number: %u\n", ntohs(header->map_number));
    printf("Current Map Level: %u\n", ntohs(header->map_level));
    printf("Current Map Filename: %s\n", header->current_map_filename);
}