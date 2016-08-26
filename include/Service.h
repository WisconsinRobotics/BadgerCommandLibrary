#ifndef _SERVICE_H
#define _SERVICE_H

#include "BclConfig.h"
#include "BclStatus.h"

#define RUN_ON_PACKET_RECEIVE 0

typedef BCL_STATUS (*ServiceExecutor)(char *buffer, int length);
typedef BCL_STATUS (*ServicePacketHandler)(BclPacket *pkt);

typedef struct
{
    uint8_t Id;
    uint8_t Active;
    uint16_t SleepInterval;
    char Name[SERVICE_MAX_NAME_LENGTH];

    // May be null - will be treated as nop by ServiceMaster
    ServiceExecutor Execute; 
    ServicePacketHandler HandlePacket;
} Service;

BCL_STATUS InitializeService (
    Service *               service,
    uint8_t                 id, 
    const char *            name,
    ServiceExecutor         execute,
    ServicePacketHandler    handler
); 

#endif