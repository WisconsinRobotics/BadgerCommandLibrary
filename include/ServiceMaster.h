#ifndef _SERVICE_MASTER_H
#define _SERVICE_MASTER_H

#include "BclConfig.h"
#include "Service.h"
#include "Subsystem.h"
#include "Net.h"
#include "Serial.h"

typedef struct
{
    Subsystem *     Subsystems[MAX_SUBSYSTEMS];

    // for now, support only 1 serial and UDP port
    SerialHandle    SerialPort;
    UdpHandle       UdpPort;

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

BCL_STATUS RegisterSerialPort (
    ServiceMaster *     serviceMaster,
    SerialHandle        handle
);

BCL_STATUS RegisterUdpPort (
    ServiceMaster *     serviceMaster,
    UdpHandle           handle
);

BCL_STATUS SendPacketOverSerial (
    ServiceMaster *        serviceMaster,
    BclPacket *            pkt
);

BCL_STATUS SendPacketOverUdp (
    ServiceMaster *        serviceMaster,
    BclPacket *            pkt,
    struct sockaddr_in     dest_addr
);

/**
    Does not return. This function will likely be platform dependent.
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