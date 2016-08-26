#ifndef _PACKET_H
#define _PACKET_H

#include <stdint.h>

#define BCL_PACKET_START                ((uint16_t)(0xBAAD))
#define BCL_PACKET_END                  ((uint8_t)(0xFE))

#define PACKET_MIN_SIZE                 10
#define PACKET_HEADER_SIZE              PACKET_MIN_SIZE


typedef void * BclPayloadPtr;

typedef BCL_STATUS (*BclPayloadSerializer) (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

typedef BCL_STATUS (*BclPayloadDeserializer) (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
);

typedef struct
{
    uint8_t Subsystem;
    uint8_t Service;
} BclAddress;

typedef struct
{
    uint8_t             Opcode;
    BclAddress          Source;
    BclAddress          Destination;
    uint8_t             PacketSize;
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
    uint8_t                 packet_size,
    BclPayloadPtr           payload,
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
);

BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
);

BCL_STATUS DeserializeBclPacket (
    BclPacket *         pkt, 
    const uint8_t *     buffer,
    uint8_t             length
);

#endif