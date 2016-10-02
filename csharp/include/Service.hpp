#pragma once

#include "Packet.hpp"
#include "ServiceMaster.hpp"

using System::Threading::Timer;

namespace BclSharp
{
    ref class ServiceMaster;

    public ref class Service
    {
    public:
        const static System::Int32 RUN_ON_PACKET_RECEIVE = -1;
        Service(System::Int32 id);
        Service(System::Int32 id, System::Int32 interval, System::Boolean active);
        ~Service();
        void ExecuteOnTime();
        virtual void Execute();
        virtual System::Boolean HandlePacket(array<System::Byte>^ buffer, System::Int32 length);
        property System::Boolean IsActive;
        property System::Int32 SleepInterval;

    internal:
        void SetServiceMaster(ServiceMaster^ serviceMaster);

    protected:
        Timer^ execute_timer;
        ServiceMaster^ master;
        BclAddress *serviceAddr;
    };
}