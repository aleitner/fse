#include <stdio.h>
#include <stdlib.h>

#include "fse/header.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to SAVE.DAT>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *saveFile;

    // Open the SAVE.DAT file for reading in binary mode.
    saveFile = fopen(filename, "rb");
    if (saveFile == NULL) {
        fprintf(stderr, "Error opening file '%s'.\n", filename);
        return EXIT_FAILURE;
    }

    save_dat_header_t header;
    read_header(saveFile, &header);
    print_header(&header);

    // Close the file.
    fclose(saveFile);
    return EXIT_SUCCESS;
}