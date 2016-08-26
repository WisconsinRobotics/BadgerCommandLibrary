#ifndef _CRC8_H
#define _CRC8_H

#include <stdint.h>

uint8_t compute_crc8 (
    const void *    buffer,
    int             len
);

#endif