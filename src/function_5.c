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
    
    // Start searching from the beginning of the file
    fseek(file, 0, SEEK_SET);

    while ((bytes_read = fread(buffer, 1, READ_BUFFER_SIZE, file)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            // Check if we've found the function 5 signature
            if (memcmp(&buffer[i], FUNCTION_5_SIGNATURE, sizeof(FUNCTION_5_SIGNATURE)) == 0) {
                /* Calculate the actual offset (current position - buffer remaining + i) */
                offset = ftell(file) - (bytes_read - i);

                // Return the offset where the signature was found
                return offset;
            }
        }
        
        // Rewind the pointer back by the signature size to accommodate for patterns 
        // that might span across two reads
        if (bytes_read == READ_BUFFER_SIZE) {
            fseek(file, 1 - sizeof(FUNCTION_5_SIGNATURE), SEEK_CUR);
        }
    }

    // Return 0 if not found
    return 0;
}

function_5_t* load_function_5(FILE *file, uint32_t offset) {
    fseek(file, offset, SEEK_SET);

    // Read the fixed portion of function_5_t structure
    size_t fixed_part_size = offsetof(function_5_t, inventory);
    function_5_t fixed_part;
    fread(&fixed_part, fixed_part_size, 1, file);

    // Allocate memory for function_5_t structure including inventory based on item count
    size_t total_size = fixed_part_size + ntohl(fixed_part.items_in_inventory) * sizeof(item_t);
    function_5_t *function_5 = (function_5_t *)malloc(total_size);
    if (!function_5) {
        return NULL;
    }

    // Copy the fixed part into the newly allocated structure
    memcpy(function_5, &fixed_part, fixed_part_size);

    // Read the inventory items into function_5->inventory
    fread(function_5->inventory, sizeof(item_t), ntohl(fixed_part.items_in_inventory), file);

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
    printf("FID (Appearance): 0x%.8hx\n", ntohl(func5->FID));
    printf("Unknown Special: 0x%.8hx\n", ntohl(func5->unknown_special));
    printf("Map Level: %u\n", ntohl(func5->map_level));
    printf("Items in Inventory: %u\n", ntohl(func5->items_in_inventory));
    printf("Crippled Body Parts: %u\n", ntohl(func5->crippled_body_parts));
    printf("Hitpoints: %u\n", ntohl(func5->hitpoints));
    printf("Radiation Level: %u\n", ntohl(func5->radiation_level));
    printf("Poison Level: %u\n", ntohl(func5->poison_level));
}