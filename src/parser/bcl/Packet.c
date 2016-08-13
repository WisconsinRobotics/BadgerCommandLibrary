#include "Packet.h"
#include "bprintf.h"
#include "crc8.h"


BCL_STATUS InitializeBclPacket (
    BclPacket *             pkt,
    uint8_t                 opcode,
    uint8_t                 packet_size,
    BclPayloadPtr           payload
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
)
{
    // TODO
    return BCL_OK;
}

BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written,
    )
{
    // TODO
    return BCL_OK;
}

BCL_STATUS DeserializeBclPacket (
    BclPacket*          pkt, 
    const uint8_t *     buffer, 
    uint8_t             length
    )
{
    // TODO
    return BCL_OK;
}