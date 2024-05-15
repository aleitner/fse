#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include <stdio.h>

/**
 * The size of the save file signature for validation, in bytes.
 */
#define SIZE_SAVE_FILE_SIGNATURE      0x18

/**
 * The size of the game version array, in bytes.
 */
#define SIZE_VERSION                  0x04

/**
 * The size of the letter 'R' field within the header, in bytes.
 */
#define SIZE_LETTER_R                 0x01

/**
 * The size of the player's name field within the header,
 * including null terminator, in bytes.
 */
#define SIZE_PLAYER_NAME              0x20

/**
 * The size of the save game name field within the header,
 * including null terminator, in bytes.
 */
#define SIZE_SAVEGAME_NAME            0x1E

/**
 * The size of the map filename field within the header,
 * including null terminator, in bytes.
 */
#define SIZE_MAP_FILENAME             0x10

/**
 * The size of the raw BMP image data for the saved game screenshot, in bytes.
 */
#define SIZE_BMP_IMAGE                0x7460

/**
 * The size of the unused section within the header, in bytes.
 */
#define SIZE_UNUSED_ZEROES            0x80

#pragma pack(push, 1)

/**
 * Represents a header within a Fallout save file, containing metadata about
 * the save such as the player's name, game version, and time at which the
 * game was saved.
 */
typedef struct {
    /**
     * An identifier for a valid Fallout save file.
     */
    char save_file_signature[SIZE_SAVE_FILE_SIGNATURE];

    /**
     * Version of the game, formatted as a series of bytes,
     * e.g., {0x00, 0x01, 0x00, 0x02} for version 1.02.
     */
    uint8_t game_version[SIZE_VERSION];

    /**
     * A character 'R', used as part of the file validation process.
     */
    char letter_r;

    /**
     * Player's name, max 31 characters plus NULL terminator.
     */
    char player_name[SIZE_PLAYER_NAME];

    /**
     * Name of the save game as an ASCII string.
     */
    char savegame_name[SIZE_SAVEGAME_NAME];

    /**
     * The real-time day when the game was saved.
     */
    uint16_t saved_day_realtime;

    /**
     * The real-time month when the game was saved.
     */
    uint16_t saved_month_realtime;

    /**
     * The real-time year when the game was saved.
     */
    uint16_t saved_year_realtime;

    /**
     * Unused: real-time hour and minutes representation.
     * Incorrectly formatted and not used.
     */
    uint32_t hourminutes_realtime;

    /**
     * In-game month when the game was saved.
     */
    uint16_t ingame_month;

    /**
     * In-game day when the game was saved.
     */
    uint16_t ingame_day;

    /**
     * In-game year when the game was saved.
     */
    uint16_t ingame_year;

    /**
     * Number of seconds since a specific in-game date (Dec 5, 2161)
     * multiplied by 10.
     */
    uint32_t ingame_date_ticks;

    /**
     * Number of the map level from maps.txt related to the current save.
     */
    uint16_t map_level;

    /**
     * The map number from maps.txt related to the current save.
     */
    uint16_t map_number;

    /**
     * Current map filename, e.g., "ARTEMPLE.sav".
     */
    char current_map_filename[SIZE_MAP_FILENAME];

    /**
     * Raw BMP image data for the saved game screenshot.
     */
    uint8_t save_screen_bmp[SIZE_BMP_IMAGE];

    /**
     * Unused section, filled with zeroes.
     */
    uint8_t unused_zeroes[SIZE_UNUSED_ZEROES];

} header_t;
#pragma pack(pop)

/**
 * Loads the header from the provided save file and returns a pointer to a
 * newly-allocated header_t structure with the read data. If the file cannot
 * be read or the header cannot be allocated, NULL is returned.
 *
 * @param file
 *     The file from which the header will be read.
 *
 * @return
 *     A pointer to the newly-allocated header_t structure, or NULL if an
 *     error occurs.
 */
header_t* load_header(FILE *file);

/**
 * Writes a Header structure to the specified file at the given offset.
 * If an error occurs during writing, returns a nonzero error code.
 *
 * @param file
 *     The file to which the Header data will be written.
 *
 * @param func6
 *     A pointer to the header_t structure containing the data to write.
 *
 * @param offset
 *     The offset within the file where Header data should be written.
 *
 * @return
 *     Zero on successful write, or a nonzero error code on failure.
 */
int save_header(FILE *file, const header_t *header, uint32_t offset);

/**
 * Prints out the contents of a save file header in a human-readable format.
 *
 * @param header
 *     The header to be printed.
 */
void print_header(const header_t *header);

#endif