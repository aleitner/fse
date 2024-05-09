#include "fse/function_1.h"

function_1_t read_function_1(FILE *file, uint32_t offset) {
    function_1_t func1;
    fseek(file, offset, SEEK_SET); // Move the file pointer to the beginning of Function 1 data.
    fread(&func1, sizeof(func1), 1, file); // Read the Function 1 data into the struct.
    return func1;
}

void write_function_1(FILE *file, uint32_t offset, function_1_t func1) {
    fseek(file, offset, SEEK_SET); // Move the file pointer to the beginning of Function 1 data.
    fwrite(&func1, sizeof(func1), 1, file); // Write the Function 1 data from the struct to the file.
}
