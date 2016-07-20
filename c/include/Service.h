#ifndef _SERVICE_H
#define _SERVICE_H

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

    ServiceExecutor Execute; 
    ServicePacketHandler HandlePacket;
} Service;

void InitializeService(int id, Service *service);

#endif