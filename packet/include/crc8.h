#ifndef _CRC8_H
#define _CRC8_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t compute_crc8 (
    const void *    buffer,
    int             len
);

#ifdef __cplusplus
}
#endif

#endif
