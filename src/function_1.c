#include "fse/function_1.h"

#include <stdlib.h>

function_1_t* load_function_1(FILE *file, uint32_t offset) {
    if (file == NULL) {
        fprintf(stderr, "Invalid file pointer.\n");
        return NULL;
    }

    function_1_t *func1 = malloc(sizeof(function_1_t));
    if (func1 == NULL) {
        fprintf(stderr, "Memory allocation for function_1_t failed.\n");
        return NULL;
    }
    
    fseek(file, offset, SEEK_SET);
    
    size_t num_read = fread(func1, sizeof(function_1_t), 1, file);

    if (num_read != 1) {
        fprintf(stderr, "Failed to read function_1_t from file.\n");
        free(func1);
        return NULL;
    }

    return func1;
}