#ifndef _SERVICE_MASTER_H
#define _SERVICE_MASTER_H

#include "BclConfig.h"
#include "Service.h"
#include "Subsystem.h"


typedef struct
{
    Subsystem *     Subsystems[MAX_SUBSYSTEMS];

    // serial interface handle
    // network interface handle
    // how many of each to support?

    // private
    uint8_t         _allocated_bitset;
} ServiceMaster;

BCL_STATUS InitializeServiceMaster (
    ServiceMaster *     serviceMaster
);

BCL_STATUS AddSubsystem (
    ServiceMaster *     serviceMaster,
    Subsystem *         subsystem
);

BCL_STATUS RemoveSubsystem (
    ServiceMaster *     serviceMaster,
    Subsystem *         subsystem
);

BCL_STATUS RemoveSubsystemById (
    ServiceMaster *     serviceMaster,
    uint8_t             subsystem_id
);

// TODO: opening serial and network ports - need transparent interface

/**
    Does not return. This function will likely be platform depedent.
    This function will need to be able to:
    (1) Listen for messages
    (2) Dispatch incoming messages to subsystems
    (3) If there's a reply to be sent, send via same interface.
    (4) Simultaneously, we need to iterate through the subsystems
        and run any service that's due to be called.
 */
void RunServiceMaster(
    ServiceMaster *     serviceMaster
); 
#endif