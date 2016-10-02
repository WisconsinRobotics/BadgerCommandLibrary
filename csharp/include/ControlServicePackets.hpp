#pragma once

#include "Packet.hpp"
#include "ControlServicePackets.h"

namespace BclSharp
{
    public ref class ActivateServicePacket : Packet
    {
    public:
        ActivateServicePacket();
        ~ActivateServicePacket();
    };
}