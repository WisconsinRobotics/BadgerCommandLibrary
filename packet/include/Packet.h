#ifndef _PACKET_H
#define _PACKET_H

#include <stdint.h>
#include "BclStatus.h"

#define BCL_PACKET_START                ((uint16_t)(0xBAAD))
#define BCL_PACKET_END                  ((uint8_t)(0xFE))

#define PACKET_HEADER_SIZE               9
#define PACKET_MIN_SIZE                 (PACKET_HEADER_SIZE + 1) // +1 for end byte

#define BCL_HEADER_INDEX                0
#define OPCODE_INDEX                    2
#define SRC_ADDR_INDEX                  3
#define DEST_ADDR_INDEX                 5
#define PAYLOAD_SIZE_INDEX              7
#define PAYLOAD_CRC_INDEX               8
#define PAYLOAD_INDEX                   9

#define BCL_BROADCAST_ROBOT_ID          0xFF
#define BCL_BROADCAST_SERVICE_ID        0xFF

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct BclAddress
{
    uint8_t RobotID;
    uint8_t ServiceID;
} BclAddress;

typedef struct BclPacketHeader
{
    uint8_t             Opcode;
    BclAddress          Source;
    BclAddress          Destination;
    uint8_t             PayloadSize;
    uint8_t             Checksum;
} BclPacketHeader;

typedef struct BclPacket
{
    BclPacketHeader         Header;
    BclPayloadPtr           Payload;
    BclPayloadSerializer    Serialize;
    BclPayloadDeserializer  Deserialize;
} BclPacket;

/**
 * @brief The base constructor for initializing BclPacket objects.
 *
 * You should never have to supply arguments to this function, unless you
 * are creating a new packet type.
 *
 * @param pkt                       The BclPacket object to initialize.
 * @param opcode                    The packet opcode.
 * @param payload                   A pointer to a separate payload object, may be null.
 * @param payload_size              The payload size. Must be 0 if there is not payload.
 * @param BclPayloadSerializer      A function pointer to serialize the payload. Must not
 *                                      be null if there is a payload, null otherwise.
 * @param BclPayloadDeserializer    A function pointer to parse the payload. Must not be
 *                                      null if there is a payload, null otherwise.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS InitializeBclPacket (
    BclPacket *             pkt,
    uint8_t                 opcode,
    BclPayloadPtr           payload,
    uint8_t                 payload_size,
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
);

/**
 * @brief Serializes the BclPacket object into a byte buffer.
 *
 * @param pkt           The packet to serialize.
 * @param buffer        The buffer in which to serialize the packet.
 * @param length        The length of the buffer.
 * @param bytes_written An optional pointer to get how many bytes were written
 *                      into the buffer.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
);


/**
 * @brief Reads a BclPacketHeader from the buffer.
 *
 * @param header        The header in which to store the parsed data.
 * @param buffer        The buffer to parse.
 * @param length        The buffer length.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS ParseBclHeader (
    BclPacketHeader *   header,
    const uint8_t *     buffer,
    uint8_t             length
);

/**
 * @brief Parse the buffer into a BclPacket object.
 * 
 * Note: the BclPacket passed in must be initialized prior to calling this
 * function. For example, if you want to parse a buffer containing a
 * ReportHeartbeat message, you must pass in a BclPacket object that has 
 * been initialized by InitializeReportHeartbeatPacket().
 *
 * @param pkt       The packet to store the parsed data.
 * @param buffer    The raw buffer.
 * @param length    The length of the buffer.
 * @param robot_id  This robot's ID.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS DeserializeBclPacket (
    BclPacket *         pkt, 
    const uint8_t *     buffer,
    uint8_t             length
);

#ifdef __cplusplus
}
#endif

#endif
