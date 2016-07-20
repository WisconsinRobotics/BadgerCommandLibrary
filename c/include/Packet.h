#ifndef _PACKET_H
#define _PACKET_H

#include <stdint.h>

#define BCL_PACKET_START_HIGHER         0xBA
#define BCL_PACKET_START_LOWER          0xAD
#define BCL_PACKET_END                  0xFE

#define PACKET_MIN_SIZE                 10
#define PACKET_METADATA_SIZE            10
#define START_HIGHER_INDEX              0
#define START_LOWER_INDEX               1
#define OPCODE_INDEX                    2
#define SOURCE_SUBSYSTEM_INDEX          3
#define SOURCE_SERVICE_INDEX            4
#define DESTINATION_SUBSYSTEM_INDEX     5
#define DESTINATION_SERVICE_INDEX       6
#define TOTAL_SIZE_INDEX                7
#define PAYLOAD_INDEX                   8

typedef struct BclPacket BclPacket;

/* Base packet functions */
void InitializeBclPacket(BclPacket* pkt, int opcode, int packetSize);
uint8_t SerializeBclPacket(BclPacket* pkt, uint8_t* buffer, int length);
uint8_t DeserializeBclPacket(BclPacket* pkt, const uint8_t* buffer, int length);
uint8_t ComputeChecksum(uint8_t* buffer, int length);

struct BclPacket
{
    uint8_t Opcode;
    uint8_t SourceSubsytem;
    uint8_t SourceService;
    uint8_t DestinationSubsystem;
    uint8_t DestinationService;
    uint8_t PacketSize;
    uint8_t Checksum;
};

#endif