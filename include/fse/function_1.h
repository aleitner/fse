#ifndef SAVE_DAT_FUNCTION_1_H
#define SAVE_DAT_FUNCTION_1_H

#include <stdint.h>
#include <stdio.h>

#define FUNCTION_1_SIZE 4

#pragma pack(push, 1)
typedef struct {
    uint8_t data[FUNCTION_1_SIZE];
} function_1_t;
#pragma pack(pop)

function_1_t read_function_1(FILE *file, uint32_t offset);
void write_function_1(FILE *file, uint32_t offset, function_1_t func1);

#endif