#ifndef _PACKET_H
#define _PACKET_H

#include <stdint.h>
#include "BclStatus.h"

#define BCL_PACKET_START                ((uint16_t)(0xBAAD))
#define BCL_PACKET_END                  ((uint8_t)(0xFE))

#define BCL_HEADER_SIZE                 9 // rename to PACKET_HEADER_SIZE
#define PACKET_MIN_SIZE                 (BCL_HEADER_SIZE + 1) // +1 for end byte

#define BCL_HEADER_INDEX                0
#define OPCODE_INDEX                    2
#define SRC_ADDR_INDEX                  3
#define DEST_ADDR_INDEX                 5
#define PAYLOAD_SIZE_INDEX              7
#define PAYLOAD_CRC_INDEX               8
#define PAYLOAD_INDEX                   9

typedef void * BclPayloadPtr;

typedef BCL_STATUS (*BclPayloadSerializer)(
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

typedef BCL_STATUS (*BclPayloadDeserializer)(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
);

typedef struct
{
    uint8_t RobotID;
    uint8_t ServiceID;
} BclAddress;

typedef struct
{
    uint8_t             Opcode;
    BclAddress          Source;
    BclAddress          Destination;
    uint8_t             PayloadSize;
    uint8_t             Checksum;
} BclPacketHeader;

typedef struct
{
    BclPacketHeader         Header;
    BclPayloadPtr           Payload;
    BclPayloadSerializer    Serialize;
    BclPayloadDeserializer  Deserialize;
} BclPacket;

/* Base packet functions */
BCL_STATUS InitializeBclPacket (
    BclPacket *             pkt,
    uint8_t                 opcode,
    BclPayloadPtr           payload,
    uint8_t                 payload_size,
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
);

BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
);

BCL_STATUS ParseBclHeader (
    BclPacketHeader *   header,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t             robot_id
);

BCL_STATUS DeserializeBclPacket (
    BclPacket *         pkt, 
    const uint8_t *     buffer,
    uint8_t             length,
    uint8_t             robot_id
);

#endif