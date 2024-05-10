#ifndef FUNCTION_1_H
#define FUNCTION_1_H

#include <stdint.h>
#include <stdio.h>

#define FUNCTION_1_SIZE 4

#pragma pack(push, 1)
typedef struct {
    uint8_t data[FUNCTION_1_SIZE];
} function_1_t;
#pragma pack(pop)

function_1_t* load_function_1(FILE *file, uint32_t offset);

#endif