#pragma once

#include <cstdint>
#include "Messages.hpp"


#define BCL_PACKET_START_HIGHER         0xBA
#define BCL_PACKET_START_LOWER          0xAD
#define BCL_PACKET_END                  0xFE

#define PACKET_MIN_SIZE                 10
#define PACKET_METATDATA_SIZE           10
#define START_HIGHER_INDEX              0
#define START_LOWER_INDEX               1
#define OPCODE_INDEX                    2
#define SOURCE_SUBSYSTEM_INDEX          3
#define SOURCE_SERVICE_INDEX            4
#define DESTINATION_SUBSYSTEM_INDEX     5
#define DESTINATION_SERVICE_INDEX       6
#define TOTAL_SIZE_INDEX                7
#define PAYLOAD_INDEX                   8

namespace BCL
{
    class Packet
    {
    public:
        Packet(void);
        ~Packet(void);
        bool Serialize(uint8_t *buffer, uint8_t size);
        bool Deserialize(const uint8_t *buffer, uint8_t size);
        uint8_t GetOpcode(void);
        uint8_t GetSourceSubsystem(void);
        uint8_t GetSourceService(void);
        uint8_t GetDestinationSubsystem(void);
        uint8_t GetDestinationService(void);
        uint8_t GetTotalPacketSize(void);
        uint8_t GetPayloadSize(void);
        
        void SetSourceSubsystem(uint8_t subsystem);
        void SetSourceService(uint8_t service);
        void SetDestinationSubsystem(uint8_t subsystem);
        void SetDestinationService(uint8_t service);
        
    protected:
        virtual bool SerializePayload(uint8_t *buffer, uint8_t size) = 0;
        virtual bool DeserializePayload(const uint8_t *buffer, uint8_t size) = 0;
        
        uint8_t opcode; // set by child ctor
        uint8_t sourceSubsystem;
        uint8_t sourceService;
        uint8_t destinationSubsystem;
        uint8_t destinationService;
        uint8_t packetSize;   // set by child ctor. Includes payload and header/footer
        
    private:
        uint8_t ComputeChecksum(void);
    };
}
