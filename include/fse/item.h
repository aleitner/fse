#ifndef ITEM_H
#define ITEM_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t quantity;         // The quantity of this item.
    uint32_t unknown_field_1;  // Always 0.
    int32_t location;          // Location of item. Necessarily always -1 (in inventory)
    uint32_t unknown_field_2;  // Always 0.
    uint32_t unknown_field_3;  // Always 0.
    uint32_t unknown_field_4;  // Unknown, 0 for most objects. Only non-zero for some items with special/quest uses. (E.g. poison tank, rubber boots, tool). 
    uint32_t unknown_field_5;  // Unknown, 0 for most objects. Only non-zero for some items with special/quest uses. 
    uint32_t unknown_field_6;  // Always 0.
    uint32_t unknown_field_7;  // Unknown, 0 for most objects. For plant spikes, this is 1, and for sharpened poles, 2.
    uint32_t on_ground_image;  // Item's on-ground image. 
    uint32_t bitfield;         // A bitfield: 0x01000000 indicates the item is held in the right hand, 0x02000000 - in the left hand, and 0x04000000 - worn (as armor). Use of other bits is unknown. 
    uint32_t map_level;        // 0, 1, or 2. Map level, which is irrelevant since it's in inventory. 
    uint32_t object_id;        // Object ID
    int32_t unknown_field_9;   // Always -1. 
    uint32_t unknown_field_10; // For Roentgen Rum and Gamma Gulp Beer, this is 0x00000001, for all others 0. 
    uint32_t unknown_field_11; // For Roentgen Rum and Gamma Gulp Beer, this is 0x00010000, for all others 0. 
    uint32_t unknown_field_12; // Always 0.
    int32_t script_id;         // Script ID; -1 for none
    int32_t unknown_field_13;  // Always -1. 
    uint32_t num_items;        // Usually 0; for containers it is the number of items in the container. The enclosed items are the ones immediately following it. 
    uint32_t unknown_field_14; // Unknown. Non-zero only for containers.
    uint32_t unknown_field_15; // Unknown. Non-zero only for containers.
    uint32_t unknown_field_16; // Always 0.
    int32_t multiple_uses;     // Specific values depending on the item type
    int32_t ammo_type;         // For weapons. -1 if no ammo needed
} item_t;
#pragma pack(pop)

#endif