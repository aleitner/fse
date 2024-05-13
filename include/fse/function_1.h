#ifndef FUNCTION_1_H
#define FUNCTION_1_H

#include <stdint.h>
#include <stdio.h>

/**
 * Defines the size of the data array for the function_1_t structure.
 */
#define FUNCTION_1_SIZE 4

#pragma pack(push, 1)
/**
 * Represents a structure used in function 1, consisting of a fixed-size data
 * array. This structure is typically loaded from a file at a specific offset.
 */
typedef struct {
    /**
     * < An array of byte-size data elements for function_1.
     */
    uint8_t data[FUNCTION_1_SIZE];
} function_1_t;
#pragma pack(pop)

/**
 * Loads the function_1_t data from the provided file at the specified offset
 * and returns a pointer to a newly-allocated function_1_t structure with the
 * read data. If the file pointer is invalid or the memory allocation fails,
 * NULL is returned.
 *
 * @param file
 *     The file from which the function_1_t data will be read.
 *
 * @param offset
 *     The offset in the file where the function_1_t data is located.
 *
 * @return
 *     A pointer to the newly-allocated function_1_t structure or NULL if
 *     an error occurs.
 */
function_1_t* load_function_1(FILE *file, uint32_t offset);

#endif