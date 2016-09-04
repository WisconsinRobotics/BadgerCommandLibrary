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

struct Service
{
    uint8_t Id;
    uint8_t Active;
    uint16_t SleepInterval;
    char Name[MAX_SERVICE_NAME_LENGTH];
    void * Data;   // internal members are stored here

    clock_t LastTimeRun;

    // May be null - will be treated as nop by ServiceMaster
    ServiceExecutor *Execute; 
    ServicePacketHandler *HandlePacket;
};

/**
 * @brief Initializes the Service.
 *
 * @param service           Pointer to a Service object.
 * @param data              Pointer to any additional service information.
 * @param id                The service ID.
 * @param name              A friendly name describing the service, limited to MAX_SERVICE_NAME_LENGTH.
 * @param sleep_interval    Specifies how often to run the service. Use RUN_ON_PACKET_RECEIVE to have
                            the service run only when a packet is received.
 * @param execute           A pointer to the function that gets executed periodically, may be NULL.
 * @param handler           A pointer to the function that gets called when packets are received.
 * @return BCL_OK on success.
 */
BCL_STATUS InitializeService (
    Service *               service,
    void *                  data,
    uint8_t                 id, 
    const char *            name,
    uint8_t                 sleep_interval,
    ServiceExecutor         execute,
    ServicePacketHandler    handler
); 

#endif
