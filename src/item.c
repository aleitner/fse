    #include "fse/item.h"

    #include <arpa/inet.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>

    item_category_t get_item_category(uint32_t object_id) {
        size_t i;

        for (i = 0; i < sizeof(WEAPONS)/sizeof(WEAPONS[0]); i++) {
            if (WEAPONS[i].id == ntohl(object_id))
                return ITEM_WEAPON;
        }

        for (i = 0; i < sizeof(AMMO)/sizeof(AMMO[0]); i++) {
            if (AMMO[i].id == ntohl(object_id))
                return ITEM_AMMO;
        }

        for (i = 0; i < sizeof(ARMOR)/sizeof(ARMOR[0]); i++) {
            if (ARMOR[i].id == ntohl(object_id))
                return ITEM_ARMOR;
        }

        for (i = 0; i < sizeof(DRUGS)/sizeof(DRUGS[0]); i++) {
            if (DRUGS[i].id == ntohl(object_id))
                return ITEM_DRUG;
        }

        for (i = 0; i < sizeof(MISC)/sizeof(MISC[0]); i++) {
            if (MISC[i].id == ntohl(object_id))
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

        size_t fixed_part_size = offsetof(item_t, ammo_type);
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

    void free_item(item_t *item) {
        free(item);
    }

    void print_item(const item_t *item) {
        if (item == NULL) {
            printf("Item data is NULL.\n");
            return;
        }

        size_t size = get_item_size(item);
        printf("Object ID (%ld): %d\n", size, ntohl(item->object_id));

        printf("Quantity: %d\n", ntohl(item->quantity));
        printf("Unknown Field (0): 0x%.8hx\n", ntohl(item->unknown_field_1));
        printf("Location (-1=in inventory): %d\n", ntohl(item->location));
        printf("Unknown Field (0): %d\n", ntohl(item->unknown_field_2));
        printf("Unknown Field (0): %d\n", ntohl(item->unknown_field_3));
        printf("Unknown Field (0=not special quest item): 0x%.8hx\n", ntohl(item->unknown_field_4));
        printf("Unknown Field: 0x%.8hx\n", ntohl(item->unknown_field_5));
        printf("Unknown Field (0): %d\n", ntohl(item->unknown_field_6));
        printf("Unknown Field (0,1,2): %d\n", ntohl(item->unknown_field_7));
        printf("On Ground Image: 0x%.8hx\n", ntohl(item->on_ground_image));
        printf("Bitfield: 0x%.8hx\n", ntohl(item->bitfield));
        printf("Map Level: %d\n", ntohl(item->map_level));
        printf("Object ID: %d\n", ntohl(item->object_id));
        printf("Unknown Field (-1): %d\n", ntohl(item->unknown_field_9));
        printf("Unknown Field: 0x%.8hx\n", ntohl(item->unknown_field_10));
        printf("Unknown Field: 0x%.8hx\n", ntohl(item->unknown_field_11));
        printf("Unknown Field (0): %d\n", ntohl(item->unknown_field_12));
        printf("Script ID (-1=None): %d\n", ntohl(item->script_id));
        printf("Unknown Field (-1): %d\n", ntohl(item->unknown_field_13));
        printf("Unknown Field (-1): %d\n", ntohl(item->unknown_field_13));
        printf("Num items in container (0=None): %d\n", ntohl(item->num_items));
        printf("Unknown Container Field: 0x%.8hx\n", ntohl(item->unknown_field_14));
        printf("Unknown Container Field: 0x%.8hx\n", ntohl(item->unknown_field_15));
        printf("Unknown Field (0): %d\n", ntohl(item->unknown_field_16));
        printf("Multiple use: 0x%.8hx\n", ntohl(item->multiple_uses));
        printf("Ammo Type: 0x%.8hx\n", ntohl(item->ammo_type));
    }