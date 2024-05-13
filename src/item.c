    #include "fse/item.h"

    #include <arpa/inet.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>

    size_t get_item_size(const item_t* item) {
        return offsetof(item_t, ammo_type) + (is_gun_type(item->object_id) ? sizeof(uint32_t) : 0);
    }

    int is_gun_type(uint32_t object_id) {
        return 0;
    }

    item_t* read_item(FILE* file, uint32_t offset) {
        // Seek to the specified offset in the file before reading the item
        if (fseek(file, offset, SEEK_SET) != 0) {
            fprintf(stderr, "Seeking to offset %u failed.\n", offset);
            return NULL;
        }

        // Allocate memory for the entire item structure
        item_t* item = malloc(sizeof(item_t));
        if (item == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return NULL;
        }

        // Read the known part of the item structure, up to (but not including) the ammo_type
        size_t fixed_part_size = offsetof(item_t, ammo_type);
        if (fread(item, fixed_part_size, 1, file) != 1) {
            fprintf(stderr, "Failed to read fixed part of the item at offset %u.\n", offset);
            free(item);
            return NULL;
        }

        // Determine if this item is a gun and thus has an ammo_type
        int has_ammo_type = is_gun_type(item->object_id);
        if (has_ammo_type) {
            // Read the additional uint32_t for the ammo_type
            if (fread(&item->ammo_type, sizeof(uint32_t), 1, file) != 1) {
                fprintf(stderr, "Failed to read ammo_type for the item at offset %u.\n", offset);
                free(item);
                return NULL;
            }
        } 
        
        else {
            // If not a gun type, set ammo_type to a default value, such as 0
            item->ammo_type = 0;
        }

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

        if (is_gun_type(item->object_id))
            printf("Ammo type: %d\n", ntohl(item->ammo_type));
    }