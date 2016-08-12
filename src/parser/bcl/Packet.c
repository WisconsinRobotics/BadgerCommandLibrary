#include "Packet.h"

uint8_t SerializeBclPacket(BclPacket* pkt, uint8_t* buffer, int length)
{
    if (!pkt || !buffer || length <= PACKET_MIN_SIZE)
        return 0;
    
    return 1;
}

uint8_t DeserializeBclPacket(BclPacket* pkt, const uint8_t* buffer, int length)
{
    if (!pkt || !buffer || length <= PACKET_MIN_SIZE)
        return 0;
    
    return 1;
}

uint8_t ComputeChecksum(char* buffer, int length)
{
    return 0;
}