#ifndef _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include "Service.h"

#define MAX_SERVICES_PER_SUBSYSTEM 4

typedef struct 
{
    uint8_t     Id;
    Service *   Services[MAX_SERVICES_PER_SUBSYSTEM];

    // private 
    uint8_t     _allocated_bitset;
} Subsystem;

BCL_STATUS InitializeSubsystem (
    Subsystem *     subsystem
    uint8_t         id,
);

BCL_STATUS AddService (
    Subsystem *     subsystem,
    Service *       service
);

BCL_STATUS RemoveService (
    Subsystem *     subsystem,
    Service *       service
);

BCL_STATUS RemoveServiceById (
    Subsystem *     subsystem,
    uint8_t         service_id
);

#endif