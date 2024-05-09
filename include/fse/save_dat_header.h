#ifndef SAVE_DAT_HEADER_H
#define SAVE_DAT_HEADER_H

#include <stdint.h>
#include <stdio.h>

#define SIZE_SAVE_FILE_SIGNATURE      0x18
#define SIZE_VERSION                  0x04
#define SIZE_LETTER_R                 0x01
#define SIZE_PLAYER_NAME              0x20  // including null terminator
#define SIZE_SAVEGAME_NAME            0x1E  // including null terminator
#define SIZE_MAP_FILENAME             0x10  // including null terminator
#define SIZE_BMP_IMAGE                0x7460
#define SIZE_UNUSED_ZEROES            0x80

#pragma pack(push, 1)
typedef struct {
    char save_file_signature[SIZE_SAVE_FILE_SIGNATURE]; // FALLOUT SAVE FILE 
    uint8_t game_version[SIZE_VERSION];                 // e.g. 00 01 00 02 for version 1.02
    char letter_r;                                      // 'R'
    char player_name[SIZE_PLAYER_NAME];                 // Max 31 characters + NULL terminator
    char savegame_name[SIZE_SAVEGAME_NAME];             // Save game name ASCII string
    uint16_t saved_day_realtime;                        // The day the game was saved in realtime
    uint16_t saved_month_realtime;                      // The month
    uint16_t saved_year_realtime;                       // The year
    uint32_t hourminutes_realtime;                      // Incorrect time representation. (Unused)
    uint16_t ingame_month;                              // In-game month
    uint16_t ingame_day;                                // In-game day
    uint16_t ingame_year;                               // In-game year
    uint32_t ingame_date_ticks;                         // Number of seconds since Dec 5, 2161 * 10
    uint16_t map_level;                                 // Number of the map from maps.txt
    uint16_t map_number;
    char current_map_filename[SIZE_MAP_FILENAME];       // Current map filename, e.g. "ARTEMPLE.sav"
    uint8_t save_screen_bmp[SIZE_BMP_IMAGE];            // Raw BMP image data
    uint8_t unused_zeroes[SIZE_UNUSED_ZEROES];          // Unused section, filled with zeroes
} save_dat_header_t;
#pragma pack(pop)

void read_header(FILE *file, save_dat_header_t *header);
void print_header(const save_dat_header_t *header);

#endif