#pragma once

#include "Packet.hpp"
#include "Subsystem.hpp"

#define DEFAULT_SLEEP_INTERVAL 100
#define RUN_ON_PACKET_RECEIVE 0

namespace BCL
{
    class Service
    {
    public:
        Service(int serviceID);
        ~Service(void);
        BclPacket& Run(void);
        virtual bool HandlePacket(const BclPacket& packet) = 0;
        void GetFriendlyName(const char *name, int length);
        int GetSubsystemID(void);
        int GetServiceID(void);

    protected:
        BclPacket& Execute(void) = 0;

        int subsystemID;
        int serviceID;
        bool active;
        int sleepInterval;
    };
}