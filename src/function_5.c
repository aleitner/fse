#include "fse/function_5.h"

#include <arpa/inet.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUFFER_SIZE 1024

uint32_t find_function_5_offset(FILE *file) {
    uint8_t buffer[READ_BUFFER_SIZE];
    uint32_t offset = 0;
    size_t bytes_read;
    
    fseek(file, 0, SEEK_SET);

    while ((bytes_read = fread(buffer, 1, READ_BUFFER_SIZE, file)) > 0) {
        size_t comparison_limit = bytes_read >= sizeof(FUNCTION_5_SIGNATURE) - 1 ? 
                bytes_read - (sizeof(FUNCTION_5_SIGNATURE) - 1) : 
                0;
        for (size_t i = 0; i < comparison_limit; ++i) {
            if (memcmp(&buffer[i], FUNCTION_5_SIGNATURE, sizeof(FUNCTION_5_SIGNATURE) - 1) == 0) {
                offset = (ftell(file) - bytes_read) + i;
                return offset;
            }
        }
        
        if (bytes_read == READ_BUFFER_SIZE) {
            fseek(file, -(long)(sizeof(FUNCTION_5_SIGNATURE) - 1), SEEK_CUR);
        }
    }

    return 0;
}


function_5_t* load_function_5(FILE *file, uint32_t offset) {
    fseek(file, offset, SEEK_SET);

    size_t fixed_part_size = offsetof(function_5_t, inventory);
    function_5_t fixed_part;
    if (fread(&fixed_part, fixed_part_size, 1, file) != 1) {
        fprintf(stderr, "Failed to read the fixed part of function 5.\n");
        return NULL;
    }

    uint32_t items_in_inventory = ntohl(fixed_part.items_in_inventory);

    size_t function_5_size = sizeof(function_5_t) + sizeof(item_t) * items_in_inventory;
    function_5_t *function_5 = (function_5_t *)malloc(function_5_size);
    if (!function_5) {
        fprintf(stderr, "Failed to allocate memory for function_5_t structure.\n");
        return NULL;
    }

    memcpy(function_5, &fixed_part, fixed_part_size);

    uint32_t current_item_offset = offset + fixed_part_size;

    for (uint32_t i = 0; i < items_in_inventory; ++i) {
        item_t *item = read_item(file, current_item_offset);
        if (item == NULL) {
            free(function_5);
            return NULL;
        }

        function_5->inventory[i] = *item;

        free_item(item);

        current_item_offset += get_item_size(&function_5->inventory[i]);
    }

    return function_5;
}

const char* facing_to_string(uint32_t facing) {
    switch (facing) {
        case 0: return "northeast";
        case 1: return "east";
        case 2: return "southeast";
        case 3: return "southwest";
        case 4: return "west";
        case 5: return "northwest";
        default: return "invalid";
    }
}

void print_function_5(const function_5_t *func5) {
    if (func5 == NULL) {
        printf("Function 5 data is NULL.\n");
        return;
    }

    printf("Signature: 0x%.8hx\n", ntohl(func5->signature));
    printf("Coordinates: 0x%.8hx\n", ntohs(func5->coordinates));
    printf("Facing: %s\n", facing_to_string(ntohl(func5->facing)));
    // printf("FID (Appearance): 0x%.8hx\n", ntohl(func5->FID));
    // printf("Unknown Special: 0x%.8hx\n", ntohl(func5->unknown_special));
    printf("Map Level: %d\n", ntohl(func5->map_level));
    printf("Items in Inventory: %d\n", ntohl(func5->items_in_inventory));
    printf("Crippled Body Parts: %d\n", ntohl(func5->crippled_body_parts));
    printf("Hitpoints: %d\n", ntohl(func5->hitpoints));
    printf("Radiation Level: %d\n", ntohl(func5->radiation_level));
    printf("Poison Level: %d\n", ntohl(func5->poison_level));

    for (uint32_t i = 0; i < ntohl(func5->items_in_inventory); ++i) {
        printf("\n");
        print_item(&func5->inventory[i]);
    }

}

size_t get_function_5_size(const function_5_t *func5) {
    if (func5 == NULL)
        return 0;

    size_t total_size = offsetof(function_5_t, inventory);
    
    for (uint32_t i = 0; i < ntohl(func5->items_in_inventory); ++i) {
        total_size += get_item_size(&(func5->inventory[i]));
    }

    return total_size;
}

void free_function_5(function_5_t *func5) {
    free(func5);
}