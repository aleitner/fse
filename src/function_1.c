#include "fse/function_1.h"

#include <stdlib.h>

function_1_t* load_function_1(FILE *file, uint32_t offset) {
    if (file == NULL) {
        fprintf(stderr, "Invalid file pointer.\n");
        return NULL;
    }

    // Allocate memory for the function_1_t structure
    function_1_t *func1 = malloc(sizeof(function_1_t));
    if (func1 == NULL) {
        fprintf(stderr, "Memory allocation for function_1_t failed.\n");
        return NULL;
    }
    
    fseek(file, offset, SEEK_SET); // Move the file pointer to the specified offset.
    
    // Read the function_1_t structure from the file into the newly allocated memory
    size_t num_read = fread(func1, sizeof(function_1_t), 1, file);

    // Verify that fread successfully read the element
    if (num_read != 1) {
        fprintf(stderr, "Failed to read function_1_t from file.\n");
        free(func1); // Free allocated memory if read fails
        return NULL;
    }

    return func1; // Return the pointer to the loaded structure
}