#ifndef FUNCTION_5_H
#define FUNCTION_5_H

#include <stdint.h>
#include <stdio.h>

#include "fse/item.h"

/**
 * Signature to identify the start of Function 5 in the file.
 */
#define FUNCTION_5_SIGNATURE "\x00\x00\x46\x50"

#pragma pack(push, 1)

/**
 * Represents the structure of Function 5 data in a save file, which contains
 * various player-related statistics and inventory details.
 */
typedef struct {
    /** 
     * Always 0x00004650 ('FP')
     */
    uint32_t signature;

    /** 
     * Player's coordinates on the map
     */
    uint32_t coordinates;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_2;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_3;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_4;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_5;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_6;

    /** 
     * Player's facing (0 to 5)
     */
    uint32_t facing;

    /** 
     * Player FID number (appearance)
     */
    uint32_t FID;

    /** 
     * Unknown, usually 0x60002420
     */
    uint32_t unknown_special;

    /** 
     * Which level of the map the player is on
     */
    uint32_t map_level;

    /** 
     * Placeholder for unknown 4-byte value
     */
    uint32_t unknown_field_7;

    /** 
     * Light distance and intensity? Unknown 24-byte value
     */
    uint8_t unknown_field_8[24];

    /** 
     * Number of items in inventory
     */
    uint32_t items_in_inventory;

    /** 
     * Placeholder for unknown 24-byte value
     */
    uint8_t unknown_field_9[24];

    /** 
     * Bit field for crippled body parts
     */
    uint32_t crippled_body_parts;

    /** 
     * Placeholder for unknown 12-byte value
     */
    uint8_t unknown_field_10[12];

    /** 
     * Current hitpoints
     */
    uint32_t hitpoints;

    /** 
     * Radiation level
     */
    uint32_t radiation_level;

    /** 
     * Poison level
     */
    uint32_t poison_level;

    /** 
     * Flexible array member for inventory items
     */
    item_t inventory[];
} function_5_t;
#pragma pack(pop)

/**
 * Searches the provided file for the Function 5 signature and returns the
 * offset at which the signature was found. If the signature is not found,
 * returns 0.
 *
 * @param file
 *     The file to be searched for the Function 5 signature.
 *
 * @return
 *     The offset of the Function 5 signature within the file, or 0 if the
 *     signature is not found.
 */
uint32_t find_function_5_offset(FILE *file);

/**
 * Loads Function 5 data from the specified file at the given offset, returning
 * a pointer to a newly allocated function_5_t structure containing the data.
 * If an error occurs during reading or allocation, NULL is returned.
 *
 * @param file
 *     The file from which to load Function 5 data.
 *
 * @param offset
 *     The offset within the file where Function 5 data begins.
 *
 * @return
 *     A pointer to the newly allocated function_5_t structure, or NULL if
 *     an error occurs.
 */
function_5_t* load_function_5(FILE *file, uint32_t offset);

/**
 * Prints the information contained within a Function 5 structure in a
 * human-readable format.
 *
 * @param func5
 *     The function_5_t structure whose contents are to be printed.
 */
void print_function_5(const function_5_t *func5);

/**
 * Converts a facing value used within Function 5 to a human-readable string.
 *
 * @param facing
 *     The facing value to convert, ranging from 0 to 5.
 *
 * @return
 *     A human-readable string representing the facing direction, or "invalid"
 *     if the facing value is not recognized.
 */
const char* facing_to_string(uint32_t facing);

/**
 * Frees the memory allocated for a function_5_t structure.
 *
 * @param func5
 *     The function_5_t structure to be freed.
 */
void free_function_5(function_5_t *func);

/**
 * Computes the total size in bytes of a Function 5 structure including the sizes
 * of all items within its inventory. If the provided Function 5 structure pointer
 * is NULL, this function returns zero.
 * 
 * @param func5
 *     The function_5_t structure pointer from which to compute the total size.
 * 
 * @return
 *     The total size of the Function 5 structure plus its inventory items' sizes,
 *     in bytes. Returns 0 if the func5 parameter is NULL.
 */
size_t get_function_5_size(const function_5_t *func5);

#endif