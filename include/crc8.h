#ifndef _CRC8_H
#define _CRC8_H

#include <stdint.h>

/**
 * @brief Computes the CRC-8 value of the specified buffer.
 *
 * This implementation dynamically computes the CRC-8 instead of by a lookup
 * table. This function uses the DARC/CRC-8 polynomial.
 *
 * @param buffer The buffer on which to compute a CRC value.
 * @param len The length of the buffer.
 * @return A 8-bit integer containing the CRC value.
 */
uint8_t compute_crc8 (
    const void *    buffer,
    int             len
);

#endif