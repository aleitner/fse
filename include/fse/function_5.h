#ifndef FUNCTION_5_H
#define FUNCTION_5_H

#include <stdint.h>
#include <stdio.h>

#include "fse/item.h"

// Signature to identify the start of function 5
#define FUNCTION_5_SIGNATURE "\x00\x00\x46\x50"

#pragma pack(push, 1)
typedef struct {
    uint32_t signature;             // Always 0x00004650 ('FP')
    uint32_t coordinates;           // Player's coordinates on the map
    uint32_t unknown_field_2;       // Placeholder for unknown 4-byte value
    uint32_t unknown_field_3;       // Placeholder for unknown 4-byte value
    uint32_t unknown_field_4;       // Placeholder for unknown 4-byte value
    uint32_t unknown_field_5;       // Placeholder for unknown 4-byte value
    uint32_t unknown_field_6;       // Placeholder for unknown 4-byte value
    uint32_t facing;                // Player's facing (0 to 5)
    uint32_t FID;                   // Player FID number (appearance)
    uint32_t unknown_special;       // Unknown, usually 0x60002420
    uint32_t map_level;             // Which level of the map the player is on
    uint32_t unknown_field_7;       // Placeholder for unknown 4-byte value
    uint8_t unknown_field_8[24];    // Light distance and intensity? Unknown 24-byte value
    uint32_t items_in_inventory;    // Number of items in inventory
    uint8_t unknown_field_9[24];    // Placeholder for unknown 24-byte value
    uint32_t crippled_body_parts;   // Bit field for crippled body parts
    uint8_t unknown_field_10[12];   // Placeholder for unknown 12-byte value
    uint32_t hitpoints;             // Current hitpoints
    uint32_t radiation_level;       // Radiation level
    uint32_t poison_level;          // Poison level
    item_t inventory[];             // Flexible array member for inventory items
} function_5_t;
#pragma pack(pop)

// Function to find the offset of function 5 in the SAVE.DAT file
uint32_t find_function_5_offset(FILE *file);
function_5_t* load_function_5(FILE *file, uint32_t offset);
void print_function_5(const function_5_t *func5);
const char* facing_to_string(uint32_t facing);
void free_function_5(function_5_t *func5);

#endif

