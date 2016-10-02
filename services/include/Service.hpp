#pragma once

#include "Timer.hpp"
#include <chrono>
#include "ServiceMaster.hpp"
#include "Packet.h"

namespace BCL
{
    class ServiceMaster;

    class Service
    {
    public:
        const static int RUN_ON_PACKET_RECEIVE = -1;

        Service(int id);
        Service(int id, int interval, bool active);
        ~Service();
        
        void SetServiceMaster(ServiceMaster *serviceMaster);
        void ExecuteOnTime();
        virtual bool HandlePacket(const uint8_t *buffer, int length);
        int GetSleepInterval() const;
        void SetSleepInterval(int sleep_interval);
        bool IsActive() const;
        void SetActive(bool active);

    protected:
        virtual void Execute();

        ServiceMaster *serviceMaster;
        Timer execute_timer;
        BclAddress serviceAddr;
        int sleepInterval;
        bool isActive;
    };
}