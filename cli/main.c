#include <stdio.h>
#include <stdlib.h>

#include "fse/header.h"
#include "fse/function_1.h"
#include "fse/function_5.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to SAVE.DAT>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *saveFile = NULL;
    header_t *header = NULL;
    function_1_t *function_1 = NULL;
    function_5_t *function_5 = NULL;
    uint32_t function_5_offset = 0;
    int return_code = EXIT_SUCCESS;

    saveFile = fopen(filename, "rb");
    if (!saveFile) {
        fprintf(stderr, "Error opening file '%s'.\n", filename);
        return_code = EXIT_FAILURE;
        goto cleanup;
    }

    header = load_header(saveFile);
    if (!header) {
        fprintf(stderr, "Failed to load header.\n");
        return_code = EXIT_FAILURE;
        goto cleanup;
    }
    print_header(header);

    function_1 = load_function_1(saveFile, sizeof(header_t));
    if (!function_1) {
        fprintf(stderr, "Failed to load function 1 data.\n");
        return_code = EXIT_FAILURE;
        goto cleanup;
    }

    function_5_offset = find_function_5_offset(saveFile);
    if (function_5_offset == 0) {
        fprintf(stderr, "Function 5 signature not found.\n");
        return_code = EXIT_FAILURE;
        goto cleanup;
    }

    function_5 = load_function_5(saveFile, function_5_offset);
    if (!function_5) {
        fprintf(stderr, "Failed to load function 5 data.\n");
        return_code = EXIT_FAILURE;
        goto cleanup;
    }

    print_function_5(function_5);

cleanup:
    free(function_5);
    free(function_1);
    free(header);

    if (saveFile)
        fclose(saveFile);

    return return_code;
}