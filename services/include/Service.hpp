#pragma once

#include "Timer.hpp"
#include "ServiceMaster.hpp"
#include "Packet.h"
#include <chrono>
#include <memory>

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
        int GetID() const;

    protected:
        virtual void Execute();

        ServiceMaster *serviceMaster;
        std::unique_ptr<Timer> execute_timer;
        BclAddress serviceAddr;
        int sleepInterval;
        bool isActive;

    private:
        void TimerExecute();

    };
}