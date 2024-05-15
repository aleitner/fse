#include "fse/header.h"

#include "fse/endian_conversion.h"
#include <stdlib.h>

header_t* load_header(FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Invalid file pointer.\n");
        return NULL;
    }

    header_t *header = malloc(sizeof(header_t));
    if (header == NULL) {
        fprintf(stderr, "Memory allocation for header_t failed.\n");
        return NULL;
    }
    
    fseek(file, 0, SEEK_SET);

    size_t num_read = fread(header, sizeof(header_t), 1, file);

    if (num_read != 1) {
        fprintf(stderr, "Failed to read header_t from file.\n");
        free(header);
        return NULL;
    }

    return header;
}

int save_header(FILE *file, const header_t *header, uint32_t offset) {
    if (file == NULL || header == NULL) {
        fprintf(stderr, "Invalid file or structure pointer.\n");
        return 1;
    }
    
    fseek(file, offset, SEEK_SET);
    
    size_t num_written = fwrite(header, sizeof(header_t), 1, file);
    
    if (num_written != 1) {
        fprintf(stderr, "Failed to write header to file.\n");
        return 1;
    }

    fflush(file);

    return 0;
}

void print_header(const header_t *header) {
    printf("Save File Signature: %s\n", header->save_file_signature);
    printf("Game Version: %d.%d%d\n", header->game_version[1], header->game_version[2], header->game_version[3]);
    printf("Letter 'R': %c\n", header->letter_r);
    printf("Player Name: %s\n", header->player_name);
    printf("Save Game Name: %s\n", header->savegame_name);
    printf("Saved Date (Realtime): %u-%u-%u\n", 
            from_savefile_byte_order_16(header->saved_day_realtime), from_savefile_byte_order_16(header->saved_month_realtime), 
            from_savefile_byte_order_16(header->saved_year_realtime));
    printf("Saved Date (In-game): %u-%u-%u\n", 
            from_savefile_byte_order_16(header->ingame_month), from_savefile_byte_order_16(header->ingame_day), from_savefile_byte_order_16(header->ingame_year));
    printf("In-game Date Ticks: %u\n", from_savefile_byte_order_32(header->ingame_date_ticks));
    printf("Current Map Number: %u\n", from_savefile_byte_order_16(header->map_number));
    printf("Current Map Level: %u\n", from_savefile_byte_order_16(header->map_level));
    printf("Current Map Filename: %s\n", header->current_map_filename);
}