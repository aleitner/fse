#include <stdio.h>
#include <stdlib.h>

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

    // Close the file.
    fclose(saveFile);
    return EXIT_SUCCESS;
}