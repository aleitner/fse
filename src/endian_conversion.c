#include "fse/endian_conversion.h"

/**
 * Checks if the system uses little endian byte order.
 *
 * In little endian systems, the least significant byte is stored at the lowest address.
 *
 * @return
 *     1 if the system is little endian, 0 otherwise.
 */
static int is_little_endian() {
    uint16_t test = 0x1;
    char *p = (char*)&test;
    return p[0] == 0x1;
}

uint16_t from_savefile_byte_order_16(uint16_t savefile_short) {
    if (is_little_endian())
        return (savefile_short >> 8) | (savefile_short << 8);

    return savefile_short;
}

uint32_t from_savefile_byte_order_32(uint32_t savefile_long) {
    if (is_little_endian())
        return ((savefile_long >> 24) & 0xff)      | 
               ((savefile_long << 8) & 0xff0000)   | 
               ((savefile_long >> 8) & 0xff00)     | 
               ((savefile_long << 24) & 0xff000000);

    return savefile_long;
}

uint16_t to_savefile_byte_order_16(uint16_t hostshort) {
    if (is_little_endian())
        return (hostshort >> 8) | (hostshort << 8);

    return hostshort;
}

uint32_t to_savefile_byte_order_32(uint32_t hostlong) {
    if (is_little_endian())
        return ((hostlong >> 24) & 0x000000FF) |
               ((hostlong >> 8)  & 0x0000FF00) |
               ((hostlong << 8)  & 0x00FF0000) |
               ((hostlong << 24) & 0xFF000000);

    return hostlong;
}