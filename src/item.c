#include "fse/item.h"

#include "fse/endian_conversion.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

item_category_t get_item_category(uint32_t object_id) {
    size_t i;

    for (i = 0; i < sizeof(WEAPONS)/sizeof(WEAPONS[0]); i++) {
        if (WEAPONS[i].id == from_savefile_byte_order_32(object_id))
            return ITEM_WEAPON;
    }

    for (i = 0; i < sizeof(AMMO)/sizeof(AMMO[0]); i++) {
        if (AMMO[i].id == from_savefile_byte_order_32(object_id))
            return ITEM_AMMO;
    }

    for (i = 0; i < sizeof(ARMOR)/sizeof(ARMOR[0]); i++) {
        if (ARMOR[i].id == from_savefile_byte_order_32(object_id))
            return ITEM_ARMOR;
    }

    for (i = 0; i < sizeof(DRUGS)/sizeof(DRUGS[0]); i++) {
        if (DRUGS[i].id == from_savefile_byte_order_32(object_id))
            return ITEM_DRUG;
    }

    for (i = 0; i < sizeof(MISC)/sizeof(MISC[0]); i++) {
        if (MISC[i].id == from_savefile_byte_order_32(object_id))
            return ITEM_MISC;
    }

    return ITEM_UNKNOWN;
}


size_t get_item_size(const item_t* item) {
    if (!item) return 0;

    size_t size = offsetof(item_t, multiple_uses);

    item_category_t category = get_item_category(item->object_id);
    if (category == ITEM_WEAPON || category == ITEM_AMMO || category == ITEM_MISC)
        size += sizeof(item->multiple_uses);

    if (category == ITEM_WEAPON)
        size += sizeof(item->ammo_type);

    return size;
}

item_t* read_item(FILE* file, uint32_t offset) {
    if (fseek(file, offset, SEEK_SET) != 0) {
        fprintf(stderr, "Seeking to offset %u failed.\n", offset);
        return NULL;
    }

    item_t* item = malloc(sizeof(item_t));
    if (item == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    size_t fixed_part_size = offsetof(item_t, multiple_uses);
    if (fread(item, fixed_part_size, 1, file) != 1) {
        fprintf(stderr, "Failed to read fixed part of the item at offset %u.\n", offset);
        free(item);
        return NULL;
    }

    item_category_t category = get_item_category(item->object_id);
    if (category == ITEM_WEAPON || category == ITEM_AMMO || category == ITEM_MISC) {
        if (fread(&item->multiple_uses, sizeof(uint32_t), 1, file) != 1) {
            fprintf(stderr, "Failed to read multiple_uses for the item.\n");
            free(item);
            return NULL;
        }
    }

    else
        item->multiple_uses = 0;

    if (category == ITEM_WEAPON) {
        if (fread(&item->ammo_type, sizeof(uint32_t), 1, file) != 1) {
            fprintf(stderr, "Failed to read ammo_type for the item.\n");
            free(item);
            return NULL;
        }
    }
    
    else
        item->ammo_type = 0;

    return item;
}

/**
 * Looks up the description of an item by its object ID within a specified array of item information.
 *
 * This function iterates through an array of items, comparing each item's ID to the provided `object_id`.
 * If a match is found, it returns a pointer to the item's description. If no match is found, NULL is returned.
 *
 * @param items
 *     An array of item_info_t structures which contain item IDs and their corresponding descriptions.
 *
 * @param count
 *     The number of elements in the items array.
 *
 * @param object_id
 *     The unique object ID for which to find the item description.
 *
 * @return
 *     A pointer to a string containing the item's description if found, else NULL.
 */
static const char * lookup_item_description(const item_info_t items[], size_t count, uint32_t object_id) {
    for (size_t i = 0; i < count; ++i) {
        if (items[i].id == object_id) {
            return items[i].desc;
        }
    }
    return NULL;
}

/**
 * Retrieves the description of an item given its object ID and category.
 *
 * Depending on the item category, this function will search different item arrays for the given `object_id`.
 * It facilitates finding an item's description among categorized items such as weapons, ammo, armor, drugs, or
 * miscellaneous items. If the category is unknown or not handled, a string indicating an unknown category is returned.
 *
 * @param object_id
 *     The unique object ID for the item.
 *
 * @param category
 *     The category of the item, which is used to decide which array of items to search.
 *
 * @return
 *     A pointer to a string containing the item's description if found in the specified category array;
 *     "Unknown Category" if the category does not match any known one, or NULL if the item is not found.
 */
static const char * get_item_description(uint32_t object_id, item_category_t category) {
    size_t num_weapons = sizeof(WEAPONS) / sizeof(WEAPONS[0]);
    size_t num_ammo = sizeof(AMMO) / sizeof(AMMO[0]);
    size_t num_armor = sizeof(ARMOR) / sizeof(ARMOR[0]);
    size_t num_drugs = sizeof(DRUGS) / sizeof(DRUGS[0]);
    size_t num_misc_items = sizeof(MISC) / sizeof(MISC[0]);
    
    switch (category) {
        case ITEM_WEAPON:
            return lookup_item_description(WEAPONS, num_weapons, object_id);
        case ITEM_AMMO:
            return lookup_item_description(AMMO, num_ammo, object_id);
        case ITEM_ARMOR:
            return lookup_item_description(ARMOR, num_armor, object_id);
        case ITEM_DRUG:
            return lookup_item_description(DRUGS, num_drugs, object_id);
        case ITEM_MISC:
            return lookup_item_description(MISC, num_misc_items, object_id);
        default:
            return "Unknown Category";
    }
}

void print_item(const item_t *item) {
    if (item == NULL) {
        printf("Item data is NULL.\n");
        return;
    }

    item_category_t category = get_item_category(item->object_id);
    const char *item_name = get_item_description(from_savefile_byte_order_32(item->object_id), category);
    if (item_name != NULL)
        printf("Item Name: %s\n", item_name);
    
    else
        printf("Item Name: Unknown\n");

    printf("Quantity: %d\n", from_savefile_byte_order_32(item->quantity));
    // printf("Unknown Field (0): 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_1));
    printf("Location (-1=in inventory): %d\n", from_savefile_byte_order_32(item->location));
    // printf("Unknown Field (0): %d\n", from_savefile_byte_order_32(item->unknown_field_2));
    // printf("Unknown Field (0): %d\n", from_savefile_byte_order_32(item->unknown_field_3));
    // printf("Unknown Field (0=not special quest item): 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_4));
    // printf("Unknown Field: 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_5));
    // printf("Unknown Field (0): %d\n", from_savefile_byte_order_32(item->unknown_field_6));
    // printf("Unknown Field (0,1,2): %d\n", from_savefile_byte_order_32(item->unknown_field_7));
    printf("On Ground Image: 0x%.8hx\n", from_savefile_byte_order_32(item->on_ground_image));
    printf("Bitfield: 0x%.8hx\n", from_savefile_byte_order_32(item->bitfield));
    printf("Map Level: %d\n", from_savefile_byte_order_32(item->map_level));
    printf("Object ID: %d\n", from_savefile_byte_order_32(item->object_id));
    // printf("Unknown Field (-1): %d\n", from_savefile_byte_order_32(item->unknown_field_9));
    // printf("Unknown Field: 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_10));
    // printf("Unknown Field: 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_11));
    // printf("Unknown Field (0): %d\n", from_savefile_byte_order_32(item->unknown_field_12));
    printf("Script ID (-1=None): %d\n", from_savefile_byte_order_32(item->script_id));
    // printf("Unknown Field (-1): %d\n", from_savefile_byte_order_32(item->unknown_field_13));
    // printf("Unknown Field (-1): %d\n", from_savefile_byte_order_32(item->unknown_field_13));
    printf("Num items in container (0=None): %d\n", from_savefile_byte_order_32(item->num_items));
    // printf("Unknown Container Field: 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_14));
    // printf("Unknown Container Field: 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_15));
    // printf("Unknown Field (0): 0x%.8hx\n", from_savefile_byte_order_32(item->unknown_field_16));

    if (category == ITEM_WEAPON || category == ITEM_AMMO || category == ITEM_MISC)
        printf("Multiple use: 0x%.8hx\n", from_savefile_byte_order_32(item->multiple_uses));

    if (category == ITEM_WEAPON)
        printf("Ammo Type: 0x%.8hx\n", from_savefile_byte_order_32(item->ammo_type));
}

void free_item(item_t *item) {
    free(item);
}