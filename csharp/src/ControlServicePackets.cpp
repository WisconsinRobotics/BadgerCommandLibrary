#include "ControlServicePackets.hpp"

using namespace BclSharp;

ActivateServicePacket::ActivateServicePacket()
{
    InitializeActivateServicePacket(this->base_pkt);
}

ActivateServicePacket::~ActivateServicePacket()
{
}


// TODO: finish me!