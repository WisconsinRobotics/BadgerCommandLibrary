#include "Packet.hpp"

using namespace BclSharp;

Packet::Packet()
{
    this->base_pkt = new BclPacket();
}

Packet::~Packet()
{
    if (this->base_pkt)
        delete this->base_pkt;
}

array<System::Byte>^ Packet::Serialize()
{
    uint8_t bufsize = this->base_pkt->Header.PayloadSize + PACKET_MIN_SIZE;
    array<System::Byte>^ serialized = gcnew array<System::Byte>(bufsize);
    pin_ptr<uint8_t> p = &serialized[0];

    auto status = SerializeBclPacket(this->base_pkt, p, bufsize, nullptr);
    if (status != BCL_OK)
        throw gcnew System::Exception("Failed to serialize!");

    return serialized;
}

System::Boolean Packet::Deserialize(array<System::Byte>^ buffer, System::Int32 length)
{
    pin_ptr<uint8_t> p = &buffer[0];
    return DeserializeBclPacket(this->base_pkt, p, length) == BCL_OK;
}