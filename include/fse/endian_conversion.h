#ifndef ENDIAN_CONVERSION_H
#define ENDIAN_CONVERSION_H

#include <stdint.h>

/**
 * Converts a 16-bit integer from savefile byte order (big-endian)
 * to the host machine's byte order.
 *
 * @param savefile_short
 *     The 16-bit integer in savefile byte order to convert.
 *
 * @return
 *     The 16-bit integer converted to the host machine's byte order.
 */
uint16_t from_savefile_byte_order_16(uint16_t savefile_short);

/**
 * Converts a 32-bit integer from savefile byte order (big-endian)
 * to the host machine's byte order.
 *
 * @param savefile_long
 *     The 32-bit integer in savefile byte order to convert.
 *
 * @return
 *     The 32-bit integer converted to the host machine's byte order.
 */
uint32_t from_savefile_byte_order_32(uint32_t savefile_long);

/**
 * Converts a 16-bit integer from the host machine's byte order to savefile byte order
 * (big-endian).
 *
 * @param hostshort
 *     The 16-bit integer in host machine's byte order to convert.
 *
 * @return
 *     The 16-bit integer converted to savefile byte order.
 */
uint16_t to_savefile_byte_order_16(uint16_t hostshort);

/**
 * Converts a 32-bit integer from the host machine's byte order to savefile byte order
 * (big-endian).
 *
 * @param hostlong
 *     The 32-bit integer in host machine's byte order to convert.
 *
 * @return
 *     The 32-bit integer converted to savefile byte order.
 */
uint32_t to_savefile_byte_order_32(uint32_t hostlong);
#endif