#ifndef _SERVICE_H
#define _SERVICE_H

#include "BclConfig.h"
#include "BclStatus.h"
#include "Packet.h"
#include "Net.h"
#include "time.h"

#define RUN_ON_PACKET_RECEIVE 0


typedef struct Service Service;

typedef BCL_STATUS (*ServiceExecutor) (
    Service *       service
);

typedef BCL_STATUS (*ServicePacketHandler)(
    Service *               service,
    uint8_t *               buffer,
    uint8_t                 length
);

typedef void * ServiceData;

struct Service
{
    uint8_t Id;
    uint8_t Active;
    uint16_t SleepInterval;
    char Name[MAX_SERVICE_NAME_LENGTH];
    ServiceData Data;   // internal members are stored here

    clock_t LastTimeRun;

    // May be null - will be treated as nop by ServiceMaster
    ServiceExecutor *Execute; 
    ServicePacketHandler *HandlePacket;
};

BCL_STATUS InitializeService (
    Service *               service,
    ServiceData             data,
    uint8_t                 id, 
    const char *            name,
    ServiceExecutor         execute,
    ServicePacketHandler    handler
); 

#endif