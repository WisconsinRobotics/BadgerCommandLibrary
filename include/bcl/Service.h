#ifndef _SERVICE_H
#define _SERVICE_H

#include "BclStatus.h"

#define SERVICE_MAX_NAME_LENGTH 10
#define DEFAULT_SLEEP_INTERVAL 100
#define RUN_ON_PACKET_RECEIVE 0

typedef uint8_t (*ServiceExecutor)(char *buffer, int length);
typedef uint8_t (*ServicePacketHandler)(BclPacket *pkt);

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