
#include "Packet.hpp"

using namespace BCL;

Packet::Packet(void)
{   
}

Packet::~Packet(void)
{
}

bool Packet::Serialize(uint8_t *buffer, uint8_t size)
{
    if (!buffer)
        return false;
    
    if (size < PACKET_MIN_SIZE || size < this->packetSize)
        return false;
    
    if (this->packetSize < PACKET_MIN_SIZE)
        return false;
    
    buffer[START_HIGHER_INDEX] = BCL_PACKET_START_HIGHER;
    buffer[START_LOWER_INDEX] = BCL_PACKET_START_LOWER;
    buffer[OPCODE_INDEX] = this->opcode;
    buffer[SOURCE_SUBSYSTEM_INDEX] = this->sourceSubsystem;
    buffer[SOURCE_SERVICE_INDEX] = this->sourceService;
    buffer[DESTINATION_SUBSYSTEM_INDEX] = this->destinationSubsystem;
    buffer[DESTINATION_SERVICE_INDEX] = this->destinationService;
    buffer[TOTAL_SIZE_INDEX] = this->packetSize;
    
    if (!SerializePayload(buffer + PAYLOAD_INDEX, this->packetSize - PACKET_METADATA_SIZE))
       return false;
    
    buffer[this->packetSize - 2] = ComputeChecksum();
    buffer[this->packetSize - 1] = BCL_PACKET_END;
    
    return true;
}

bool Packet::Deserialize(const uint8_t *buffer, uint8_t size)
{
    // sanity checks
    if (!buffer || size < PACKET_MIN_SIZE || this->packetSize < PACKET_MIN_SIZE)
        return false;
    
    if (buffer[START_HIGHER_INDEX] != BCL_PACKET_START_HIGHER)
        return false;
    
    if (buffer[START_LOWER_INDEX] != BCL_PACKET_START_LOWER)
        return false;
    
    if (buffer[size - 1] != BCL_PACKET_END)
        return false;
    
    if (buffer[this->packetSize - 1] != BCL_PACKET_END)
        return false;
    
    // these variables should already be set by subclass ctor
    if (buffer[OPCODE_INDEX] != this->opcode)
        return false;
    
    if (buffer[TOTAL_SIZE_INDEX] != this->packetSize)
        return false;
    
    this->sourceSubsystem = buffer[SOURCE_SUBSYSTEM_INDEX];
    this->sourceService = buffer[SOURCE_SERVICE_INDEX];
    this->destinationSubsystem = buffer[DESTINATION_SUBSYSTEM_INDEX];
    this->destinationService = buffer[DESTINATION_SERVICE_INDEX];
    
    /* TODO: checksum check */
    
    return this->DeserializePayload(buffer + PAYLOAD_INDEX, this->packetSize - PACKET_METADATA_SIZE);
}

uint8_t Packet::GetOpcode(void)
{
    return this->opcode;
}

uint8_t Packet::GetSourceSubsystem(void)
{
    return this->sourceSubsystem;
}

uint8_t Packet::GetSourceService(void)
{
    return this->sourceService;
}

uint8_t Packet::GetDestinationSubsystem(void)
{
    return this->destinationSubsystem;
}

uint8_t Packet::GetDestinationService(void)
{
    return this->destinationService;
}

uint8_t Packet::GetTotalPacketSize(void)
{
    return this->packetSize;
}

uint8_t Packet::GetPayloadSize(void)
{
    return this->payloadSize;
}

uint8_t ComputeChecksum(void)
{
    // TODO
    return 0;
}