#include "Packet.h"

uint8_t SerializeBclPacket(BclPacket *pkt, char *buffer, int length)
{
    if (!pkt || !buffer || length <= 0)
        return 0;
    
    return 1;
}

uint8_t DeserializeBclPacket(BclPacket *pkt, const char *buffer, int length)
{
    if (!pkt || !buffer || length <= 0)
        return 0;
    
    return 1;
}

uint8_t ComputeChecksum(char *buffer, int length)
{
}