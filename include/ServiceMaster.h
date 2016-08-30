#ifndef _SERVICE_MASTER_H
#define _SERVICE_MASTER_H

#include "BclConfig.h"
#include "Service.h"
#include "Net.h"
#include "Serial.h"

typedef struct
{
    Service *           Services[MAX_SERVICES];

    // support only 1 serial and one UDP endpoint 
    SerialHandle        SerialPort;
    UdpHandle           UdpPort;
    struct sockaddr_in  UdpEndpoint;

} ServiceMaster;

BCL_STATUS InitializeServiceMaster (
    ServiceMaster *     serviceMaster
);

BCL_STATUS BclRegisterService (
    ServiceMaster *     serviceMaster,
    Service *         subsystem
);

BCL_STATUS RegisterSerialPort (
    ServiceMaster *     serviceMaster,
    SerialHandle        handle
);

BCL_STATUS RegisterUdpEndpoint (
    ServiceMaster *         serviceMaster,
    UdpHandle               handle,
    struct sockaddr_in      dest_addr
);

BCL_STATUS SendPacketOverSerial (
    ServiceMaster *         serviceMaster,
    BclPacket *             pkt
);

BCL_STATUS SendPacketOverUdp (
    ServiceMaster *         serviceMaster,
    BclPacket *             pkt,
    struct sockaddr_in      dest_addr
);

void RunServiceMaster(
    ServiceMaster *     serviceMaster
); 
#endif