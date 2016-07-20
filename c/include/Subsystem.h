#ifndef _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include "Service.h"

#define MAX_SERVICES_PER_SUBSYSTEM 4

typedef struct 
{
    uint8_t Id;
    Service Services[MAX_SERVICES_PER_SUBSYSTEM];

    // private 
    uint8_t _allocated_bitset;
} Subsystem;

void InitializeSubsystem(int id, Subsystem *subsystem);

#endif