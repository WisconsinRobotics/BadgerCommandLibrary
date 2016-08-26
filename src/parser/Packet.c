#include "Packet.h"
#include "bprintf.h"
#include "crc8.h"

#define PACKET_HEADER_FMT_STR  "scccccc" 

BCL_STATUS InitializeBclPacket (
    BclPacket *             pkt,
    uint8_t                 opcode,
    uint8_t                 packet_size,
    BclPayloadPtr           payload
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
)
{
    if (!pkt || packet_size < PACKET_MIN_SIZE)
        return BCL_INVALID_PARAMETER;
    
    // a null payload is acceptable only if
    // the packet size is the minimum packet size
    if (packet_size != PACKET_MIN_SIZE)
    {
        if (!payload || !serialize_func || !deserialize_func)
            return BCL_INVALID_PARAMETER;
    }

    pkt->Header.Opcode = opcode;
    pkt->Header.Source = {0, 0};
    pkt->Header.Destination = {0, 0};
    pkt->Header.PacketSize = packet_size;

    pkt->Payload = payload;
    pkt->Serialize = serialize_func;
    pkt->Deserialize = deserialize_func;

    return BCL_OK;
}

BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written,
    )
{
    uint8_t buf_index;
    uint8_t checksum;

    if (!pkt || !buffer || pkt->PacketSize < PACKET_MIN_SIZE)
        return BCL_INVALID_PARAMETER;

    if (length < pkt->PacketSize)
        return BCL_BUFFER_TOO_SMALL;

    // write the header
    buf_index = bprintf(
        buffer, 
        length, 
        PACKET_HEADER_FMT_STR, 
        Big,
        BCL_PACKET_START,
        pkt->Header.Opcode,
        pkt->Header.Source.Subsystem,
        pkt->Header.Source.Service,
        pkt->Header.Destination.Subsystem,
        pkt->Header.Destination.Service,
        pkt->Header.PacketSize
    );

    // TODO: Create proper error code
    if (buf_index <= 0)
        return BCL_GENERIC_ERROR;

    // write the payload
    if (pkt->Payload && pkt->Serialize)
    {
        BCL_STATUS status;
        uint8_t payload_bytes_written;

        status = pkt->Serialize (
            pkt->payload, 
            buffer + buf_index, 
            length - buf_index,
            &payload_bytes_written
        );

        if (status != BCL_OK)
            return status;

        buf_index += payload_bytes_written;
    }

    // compute checksum
    checksum = compute_crc8(buffer, buf_index);

    // write checksum and end byte
    buffer[buf_index] = checksum;
    buffer[buf_index + 1] = BCL_PACKET_END;

    // final sanity check - did we match PacketSize?
    // TODO: replace with proper error
    if (buf_index + 1 != pkt->PacketSize)
        return BCL_GENERIC_ERROR;

    if (bytes_written)
        *bytes_written = buf_index + 1;

    return BCL_OK;
}

BCL_STATUS DeserializeBclPacket (
    BclPacket *         pkt, 
    const uint8_t *     buffer, 
    uint8_t             length
    )
{
    uint16_t pkt_start_val;
    uint8_t opcode;
    uint8_t packet_size;
    BclAddress source;
    BclAddress dest;
    uint8_t parsed_checksum;
    uint8_t computed_checksum;
    uint8_t bytes_scanned;

    if (!pkt || !buffer || pkt->PacketSize < PACKET_MIN_SIZE)
        return BCL_INVALID_PARAMETER;
    
    if (pkt->PacketSize > PACKET_MIN_SIZE)
    {
        if (!pkt->Deserialize || !pkt->Payload)
            return BCL_INVALID_PARAMETER;
    }

    // scan header
    bytes_scanned = bscanf(
        (const char *) buffer,
        length,
        PACKET_HEADER_FMT_STR,
        Big,
        &pkt_start_val,
        &pkt_end_val,
        &opcode,
        &packet_size,
        &source.Subsystem,
        &source.Service,
        &dest.Subsystem,
        &dest.Service,
    );

    // TODO: Create proper error code
    if (bytes_scanned <= 0)
        return BCL_GENERIC_ERROR;

    // verify header
    if (pkt_start_val != BCL_PACKET_START)
        return BCL_GENERIC_ERROR;

    if (pkt->opcode != opcode)
        return BCL_GENERIC_ERROR;
    
    if (pkt->PacketSize != packet_size)
        return BCL_GENERIC_ERROR;

    // verify end bytes
    if (buffer[packet_size - 1] != BCL_PACKET_END)
        return BCL_GENERIC_ERROR;

    computed_checksum = compute_crc8(buffer, packet_size - 2);
    parsed_checksum = buffer[packet_size - 2];
    if (computed_checksum != parsed_checksum)
        return BCL_CHECKSUM_ERROR;

    pkt->Source = source;
    pkt->Destination = dest;

    // parse payload
    if (!pkt->Deserialize)
        return BCL_OK;

    return pkt->Deserialize (
        pkt->payload,
        buffer + bytes_scanned,
        length - PACKET_MIN_SIZE,
        NULL
    );
}