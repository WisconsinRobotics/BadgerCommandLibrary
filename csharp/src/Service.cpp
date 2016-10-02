#include "Service.hpp"
#include <functional>

using namespace BclSharp;
using System::Threading::TimerCallback;

void ExecuteTimerCallback(System::Object^ service)
{
    static_cast<Service^>(service)->Execute();
}

Service::Service(System::Int32 id)
{
    this->SleepInterval = Service::RUN_ON_PACKET_RECEIVE;
    this->IsActive = false;
    this->serviceAddr = new BclAddress();
    this->serviceAddr->ServiceID = id;
}

Service::Service(System::Int32 id, System::Int32 interval, System::Boolean active)
{
    this->SleepInterval = interval;
    this->IsActive = active;
    this->serviceAddr = new BclAddress();
    this->serviceAddr->ServiceID = id;
}

Service::~Service()
{
    if (this->serviceAddr)
        delete this->serviceAddr;
}

void Service::ExecuteOnTime()
{
    this->execute_timer = gcnew Timer(gcnew TimerCallback(&ExecuteTimerCallback), this, 0, this->SleepInterval);
}

void Service::Execute()
{
}

System::Boolean Service::HandlePacket(array<System::Byte>^ buffer, System::Int32 length)
{
    return false;
}

void Service::SetServiceMaster(ServiceMaster^ serviceMaster)
{
    this->master = serviceMaster;
}
