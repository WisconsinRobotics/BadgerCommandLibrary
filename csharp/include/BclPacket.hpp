#pragma once

#include "Packet.h"

namespace BclSharp
{
    public ref class Packet
    {
    public:
        Packet();
        ~Packet();

    protected:
        BclPacket *base_pkt;
    };
}