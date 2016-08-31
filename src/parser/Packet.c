#include "Packet.h"
#include "crc8.h"
#include <string.h>


BCL_STATUS InitializeBclPacket (
    BclPacket *             pkt,
    uint8_t                 opcode,
    BclPayloadPtr           payload,
    uint8_t                 payload_size,
    BclPayloadSerializer    serialize_func,
    BclPayloadDeserializer  deserialize_func
    )
{
    if (!pkt)
        return BCL_INVALID_PARAMETER;
    
    // a null payload is acceptable only if
    // the packet size is the minimum packet size
    if (payload_size != 0)
    {
        if (!payload || !serialize_func || !deserialize_func)
            return BCL_INVALID_PARAMETER;
    }

    pkt->Header.Opcode = opcode;
    memset(&pkt->Header.Source, 0, sizeof(BclAddress));
    memset(&pkt->Header.Destination, 0, sizeof(BclAddress));
    pkt->Header.PayloadSize = payload_size;

    pkt->Payload = payload;
    pkt->Serialize = serialize_func;
    pkt->Deserialize = deserialize_func;

    return BCL_OK;
}

BCL_STATUS SerializeBclPacket (
    BclPacket *         pkt,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
    )
{
    uint8_t payload_bytes_written;

    if (!pkt || !buffer)
        return BCL_INVALID_PARAMETER;

    if (length < PACKET_MIN_SIZE + pkt->Header.PayloadSize)
        return BCL_BUFFER_TOO_SMALL;

    // write the header
    buffer[BCL_HEADER_INDEX ] = (uint8_t) (BCL_PACKET_START >> 8);
    buffer[BCL_HEADER_INDEX  + 1] = (uint8_t) (BCL_PACKET_START & 0xFF);
    buffer[OPCODE_INDEX] = pkt->Header.Opcode;
    buffer[SRC_ADDR_INDEX] = pkt->Header.Source.RobotID;
    buffer[SRC_ADDR_INDEX + 1] = pkt->Header.Source.ServiceID;
    buffer[DEST_ADDR_INDEX] = pkt->Header.Destination.RobotID;
    buffer[DEST_ADDR_INDEX + 1] = pkt->Header.Destination.ServiceID;
    buffer[PAYLOAD_SIZE_INDEX] = pkt->Header.PayloadSize;

    // write the payload
    if (pkt->Payload && pkt->Serialize)
    {
        BCL_STATUS status = pkt->Serialize (
            pkt->Payload, 
            buffer + PAYLOAD_INDEX, 
            length - PACKET_MIN_SIZE,
            &payload_bytes_written
        );

        if (status != BCL_OK)
            return status;

        // sanity check
        if (payload_bytes_written != pkt->Header.PayloadSize)
            return BCL_GENERIC_ERROR;
    }

    // compute checksum
    buffer[PAYLOAD_CRC_INDEX] = compute_crc8(buffer + PAYLOAD_INDEX, pkt->Header.PayloadSize);

    // write end byte
    buffer[PAYLOAD_INDEX + pkt->Header.PayloadSize] = BCL_PACKET_END;

    if (bytes_written)
        *bytes_written = PACKET_MIN_SIZE + pkt->Header.PayloadSize;

    return BCL_OK;
}

BCL_STATUS ParseBclHeader (
    BclPacketHeader *   header,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t             robot_id
    )
{
    if (!header || !buffer)
        return BCL_INVALID_PARAMETER;
    if (length < BCL_HEADER_SIZE)
        return BCL_BUFFER_TOO_SMALL;

    // parse buffer
    uint16_t buf_hdr = buffer[BCL_HEADER_INDEX ] | buffer[BCL_HEADER_INDEX  + 1];
    uint8_t opcode = buffer[OPCODE_INDEX];

    BclAddress srcAddr;
    srcAddr.RobotID = buffer[SRC_ADDR_INDEX];
    srcAddr.ServiceID = buffer[SRC_ADDR_INDEX + 1];

    BclAddress destAddr;
    destAddr.RobotID = buffer[DEST_ADDR_INDEX];
    destAddr.ServiceID = buffer[DEST_ADDR_INDEX + 1];

    uint8_t payloadSize = buffer[PAYLOAD_SIZE_INDEX];
    uint8_t payloadCrc = buffer[PAYLOAD_CRC_INDEX];

    // basic header verification
    if (buf_hdr != BCL_PACKET_START)
        return BCL_BAD_PACKET_START;

    if (destAddr.RobotID != robot_id)
        return BCL_ROBOT_ID_MISMATCH;

    if (PAYLOAD_INDEX + payloadSize >= length)
        return BCL_CLIPPED_PACKET;

    if (buffer[PAYLOAD_INDEX + payloadSize] != BCL_PACKET_END)
        return BCL_BAD_PACKET_END;

    uint8_t computed_crc = compute_crc8(buffer + PAYLOAD_INDEX, length - BCL_HEADER_SIZE);
    if (computed_crc != payloadCrc)
        return BCL_CHECKSUM_ERROR;

    // header OK, copy
    header->Opcode = opcode;
    header->Source = srcAddr;
    header->Destination = destAddr;
    header->PayloadSize = payloadSize;
    header->Checksum = payloadCrc;

    return BCL_OK;
}

BCL_STATUS DeserializeBclPacket (
    BclPacket *         pkt, 
    const uint8_t *     buffer, 
    uint8_t             length,
    uint8_t             robot_id
    )
{
    BclPacketHeader header;

    if (!pkt || !buffer || length < PACKET_MIN_SIZE)
        return BCL_INVALID_PARAMETER;
    
    // nonzero payload size must have a deserialze function
    if (length > PACKET_MIN_SIZE)
    {
        if (!pkt->Deserialize || !pkt->Payload)
            return BCL_INVALID_PARAMETER;
    }

    // parse header with sanity checks
    BCL_STATUS header_parse_status = ParseBclHeader (
        &header,
        buffer,
        length,
        robot_id
    );

    if (header_parse_status != BCL_OK)
        return header_parse_status;

    if (header.Opcode != pkt->Header.Opcode)
        return BCL_OPCODE_MISMATCH;

    // header OK, copy
    pkt->Header = header;

    // parse payload
    if (!pkt->Deserialize)
        return BCL_OK;

    return pkt->Deserialize (
        pkt->Payload,
        buffer + PAYLOAD_INDEX,
        length - PACKET_MIN_SIZE,
        NULL
    );
}