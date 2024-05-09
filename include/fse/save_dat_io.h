#ifndef SAVE_DAT_IO_H
#define SAVE_DAT_IO_H

#include <stdint.h>
#include <stdio.h>

// Defines for getting and setting bytes and strings (no endianness conversion needed)
void get_bytes(FILE *file, uint32_t offset, void *buffer, size_t size);
void set_bytes(FILE *file, uint32_t offset, const void *buffer, size_t size);

// Specialized getter and setter for uint16_t, taking endianness into account
void get_uint16_t(FILE *file, uint32_t offset, uint16_t *value);
void set_uint16_t(FILE *file, uint32_t offset, uint16_t value);

// Specialized getter and setter for uint32_t, taking endianness into account
void get_uint32_t(FILE *file, uint32_t offset, uint32_t *value);
void set_uint32_t(FILE *file, uint32_t offset, uint32_t value);

#endif