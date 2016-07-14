#include "Messages.hpp"

using namespace BCL;

ActivateService::ActivateService(int subsystemID, int serviceID)
{
    this->subsystemID = subsystemID;
    this->servieID = serviceID;
}

ActivateService::~ActivateService()
{
}

int ActivateService::GetSubsystemID()
{
    return this->subsystemID;
}

int ActivateService::GetServiceID()
{
    return this->serviceID;
}

void ActivateService::SetSubsystemID(int subsystemID)
{
    this->subsystemID = subsystemID;
}

void ActivateService::SetServiceID(int serviceID)
{
    this->serviceID = serviceID;
}

DeactivateService::DeactivateService(int subsystemID, int serviceID)
{
    this->subsystemID = subsystemID;
    this->servieID = serviceID;
}

DeactivateService::~DeactivateService()
{
}

int DeactivateService::GetSubsystemID()
{
    return this->subsystemID;
}

int DeactivateService::GetServiceID()
{
    return this->serviceID;
}

void DeactivateService::SetSubsystemID(int subsystemID)
{
    this->subsystemID = subsystemID;
}

void DeactivateService::SetServiceID(int serviceID)
{
    this->serviceID = serviceID;
}

QueryServiceList::QueryServiceList()
{
}

QueryServiceList::~QueryServiceList()
{
}

QueryServiceStatus::QueryServiceStatus()
{
}

QueryServiceStatus::~QueryServiceStatus()
{
}

QueryHeartbeat::QueryHeartbeat()
{
}

QueryHeartbeat::~QueryHeartbeat()
{
}

ReportServiceList::ReportServiceList()
{
}

ReportServiceList::~ReportServiceList()
{
}

ReportHeartbeat::ReportHeartbeat()
{
}

ReportHeartbeat::~ReportHeartbeat()
{
}

ReportServiceStatus::ReportServiceStatus()
{
}

ReportServiceStatus::~ReportServiceStatus()
{
}
