#include "crc8.h"

/* 
 * TODO: explain CRC impl and what it is.
 * If you've heard of the parity bit, that's CRC-1 - crc with 1 bit!
 * Algebra approach:
 * Remember algebra? You had to do polynomial long divison at some point.
 * Guess what - CRC is the exact same thing, except this time with bits. 
 * Imagine your byte buffer as a stream of bits. Convert that into a
 * polynomial. For example, the bits '1011' is x^3 + x + 1. 
 * Take your CRC polynomial (academics spend lifetimes determining "optimal"
 * polynomials!) and transform it into an algebraic form. Now divide the 
 * converted bitstream with the transformed algebraic CRC polynomial. Once
 * you're done, the remainder is the CRC value.
 *  
 * Impl notes:
 * This impl is more or less a glorified shift register with a couple extra
 * gates. Store the byte that is being processed in the high byte of the
 * shift register (in this case, the variable crc). Then, we begin the 
 * long division. We check if we can divide in the first place by checking
 * if the MSB is set (CRC-X polynomial division always has the MSB set). If it is,
 * then "subtract". Otherwise, keep shifting.
 * 
 */

// CRC-8
// poly: 0x07

uint8_t compute_crc8(const void *buffer, int len)
{
    const uint8_t *data = (const uint8_t *)buffer;
    uint8_t crc = 0;
    uint8_t i, j;

    for (i = 0; i < len; i++)
    {
        // set up the dividend
        crc ^= data[i];

        for (j = 0; j < 8; j++)
        {
            // Does the divisor go into the dividend?
            if (crc & 0x80)
            {
                // dividend -= divisor
                crc = (crc << 1) ^ 0x07;
            }
            else
            {
                // move to the next bit
                crc <<= 1;
            }
        }
    }

    // the remainder is in lower byte, so truncate
    return crc;
}
