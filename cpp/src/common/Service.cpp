#include "Service.hpp"

using namespace BCL;

Service::Service(int subsystemID, int serviceID)
{
    this->subsystemID = subsystemID;
    this->servieID = serviceID;
}

Service::~Service()
{
}

Packet& Service::Run()
{
}

virtual bool Service::HandlePacket(const BclPacket& packet) = 0
{
}

void Service::GetFriendlyName(const char *name, int length)
{
}

int Service::GetSubsystemID()
{
    return this->subsystemID;
}

int Service::GetServiceID()
{
    return this->serviceID;
}

bool Service::GetLiveness()
{
    return this->active;
}

void Service::SetLiveness(bool active)
{
    this->active = active;
}

Packet& Service::Execute() = 0
{
}
