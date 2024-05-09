#include "fse/save_dat_io.h"

#include <arpa/inet.h>

// Defines for getting and setting bytes and strings (no endianness conversion needed)
void get_bytes(FILE *file, uint32_t offset, void *buffer, size_t size) {
    fseek(file, offset, SEEK_SET);
    fread(buffer, 1, size, file);
}

void set_bytes(FILE *file, uint32_t offset, const void *buffer, size_t size) {
    fseek(file, offset, SEEK_SET);
    fwrite(buffer, 1, size, file);
}

// Specialized getter and setter for uint16_t, taking endianness into account
void get_uint16_t(FILE *file, uint32_t offset, uint16_t *value) {
    fseek(file, offset, SEEK_SET);
    fread(value, sizeof(uint16_t), 1, file);
    *value = ntohs(*value);
}

void set_uint16_t(FILE *file, uint32_t offset, uint16_t value) {
    value = htons(value);
    fseek(file, offset, SEEK_SET);
    fwrite(&value, sizeof(uint16_t), 1, file);
}

// Specialized getter and setter for uint32_t, taking endianness into account
void get_uint32_t(FILE *file, uint32_t offset, uint32_t *value) {
    fseek(file, offset, SEEK_SET);
    fread(value, sizeof(uint32_t), 1, file);
    *value = ntohl(*value);
}

void set_uint32_t(FILE *file, uint32_t offset, uint32_t value) {
    value = htonl(value);
    fseek(file, offset, SEEK_SET);
    fwrite(&value, sizeof(uint32_t), 1, file);
}