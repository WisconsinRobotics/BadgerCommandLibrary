#ifndef _SERVICE_MASTER_H
#define _SERVICE_MASTER_H

#include "Service.h"
#include "Subsystem.h"

#define MAX_SUBSYSTEMS 8

typedef struct
{
    Subsystem Subsystems[MAX_SUBSYSTEMS];
    uint8_t _allocated_bitset;
} ServiceMaster;

void InitializeServiceMaster(ServiceMaster *serviceMaster);
uint8_t AddSubsystem(ServiceMaster *serviceMaster, Subsystem *subsystem);
void RemoveSubsystem(ServiceMaster *serviceMaster, int subsystemID);

// TODO: opening serial and network ports - need transparent interface

void ServiceMasterRun(ServiceMaster *serviceMaster); // does not return
#endif