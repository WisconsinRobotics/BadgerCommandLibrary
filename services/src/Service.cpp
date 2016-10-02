#include "Service.hpp"
#include <functional>

using namespace BCL;

Service::Service(int id)
{
    this->serviceAddr.ServiceID = id;
    this->sleepInterval = RUN_ON_PACKET_RECEIVE;
    this->isActive = false;
}

Service::Service(int id, int interval, bool active)
{
    this->serviceAddr.ServiceID = id;
    this->sleepInterval = interval;
    this->isActive = active;
}

Service::~Service()
{
    this->execute_timer.Stop();
}

void Service::Execute()
{
}

void Service::SetServiceMaster(ServiceMaster *sm)
{
    this->serviceMaster = sm;
    this->serviceAddr.RobotID = sm->GetRobotID();
}

bool Service::HandlePacket(const uint8_t *buffer, int length)
{
    return false;
}

int Service::GetSleepInterval() const
{
    return this->sleepInterval;
}

void Service::SetSleepInterval(int sleep_interval)
{
    this->sleepInterval = sleep_interval;
}

bool Service::IsActive() const
{
    return this->isActive;
}

void Service::SetActive(bool active)
{
    this->isActive = active;
}

void Service::ExecuteOnTime()
{
    if (this->sleepInterval == RUN_ON_PACKET_RECEIVE)
        return;

    execute_timer.SetCallback(std::bind(&Service::Execute, this));
    execute_timer.SetPeriod(std::chrono::milliseconds(this->sleepInterval));
    execute_timer.SetPeriodic(true);
    execute_timer.Start();
}


