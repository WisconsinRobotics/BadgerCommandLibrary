#include "Service.hpp"
#include <functional>

using namespace BCL;

Service::Service(int id) : Service(id, RUN_ON_PACKET_RECEIVE, false)
{
}

Service::Service(int id, int interval, bool active) :
    execute_timer(new Timer(Interval(0), nullptr, false))
{
    this->serviceAddr.ServiceID = static_cast<uint8_t>(id);
    SetSleepInterval(interval);
    this->isActive = active;

    execute_timer->SetCallback(std::bind(&Service::TimerExecute, this));
    execute_timer->Start();
}

Service::~Service()
{
    if (this->execute_timer)
        this->execute_timer->Stop();
}

void Service::Execute()
{
}

void Service::SetServiceMaster(ServiceMaster *sm)
{
    this->serviceMaster = sm;
    this->serviceAddr.RobotID = static_cast<uint8_t>(sm->GetRobotID());
}

bool Service::HandlePacket(const uint8_t *buffer, int length)
{
    (void) buffer, length;
    return false;
}

int Service::GetSleepInterval() const
{
    return this->sleepInterval;
}

void Service::SetSleepInterval(int sleep_interval)
{
    this->sleepInterval = sleep_interval;

    // if we change the interval, we need to stop the timer
    if (this->isActive)
        execute_timer->Stop();

    // if new sleep interval is event based, we're done
    if (this->sleepInterval == Service::RUN_ON_PACKET_RECEIVE)
        return;

    // otherwise restart the timer
    execute_timer->SetPeriod(std::chrono::milliseconds(this->sleepInterval));
    execute_timer->SetPeriodic(true);
    if (this->isActive)
        execute_timer->Start();
}

bool Service::IsActive() const
{
    return this->isActive;
}

void Service::SetActive(bool active)
{
    this->isActive = active;
}

int Service::GetID() const
{
    return this->serviceAddr.ServiceID;
}

void Service::ExecuteOnTime()
{
    if (this->sleepInterval == RUN_ON_PACKET_RECEIVE)
        this->Execute();
}

void Service::TimerExecute()
{
    if (this->isActive)
        this->Execute();
}
