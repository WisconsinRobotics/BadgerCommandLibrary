#ifndef _BADGER_COMMAND_LIBRARY_H
#define _BADGER_COMMAND_LIBRARY_H

// TODO: includes and relevant defines go here

/**
 * CRC8 polynomial used to checksum packets.
 * Selected for good hamming distance (5).
 * See https://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
 */
#define BCL_CRC8_POLY            (0x9C)

#endif