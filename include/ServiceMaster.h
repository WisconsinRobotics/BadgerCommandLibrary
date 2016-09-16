#ifndef _SERVICE_MASTER_H
#define _SERVICE_MASTER_H

#include "BclConfig.h"
#include "Service.h"
#include "Net.h"
#include "Serial.h"

typedef struct
{
    Service *           Services[MAX_SERVICES];
    uint8_t             RobotID;

    // support only 1 serial and one UDP endpoint 
    SerialHandle        SerialPort;
    UdpHandle           UdpPort;
    struct sockaddr_in  UdpEndpoint;

} ServiceMaster;

/**
 * @brief Initializes a ServiceMaster struct.
 *
 * @param serviceMaster     A pointer to a ServiceMaster struct.
 * @return BCL_OK on success.
 */
BCL_STATUS InitializeServiceMaster (
    ServiceMaster *     serviceMaster,
    uint8_t             robot_id
);

/** 
 * @brief Adds a Service to the ServiceMaster for periodic execution.
 *
 * All services must be registered prior to running the service master.
 *
 * @param serviceMaster         The ServiceMaster struct in which to bind the service.
 * @param service               The Service to bind to the ServiceMaster.
 * @return BCL_OK on success.
 */
BCL_STATUS RegisterService (
    ServiceMaster *     serviceMaster,
    Service *           service
);

/**
 * @brief Binds a serial port to the ServiceMaster struct.
 *
 * @param serviceMaster         The ServiceMaster struct in whch to bind the serial port.
 * @param handle                A valid serial port handle.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS RegisterSerialPort (
    ServiceMaster *     serviceMaster,
    SerialHandle        handle
);

/**
 * @brief Binds a UDP socket to the ServiceMaster struct.
 *
 * @param serviceMaster         The ServiceMaster struct in whch to bind the serial port.
 * @param handle                A valid UDP socket handle.
 * @param dest_addr             
 * @return BCL_OK on success, or BCL_UNSUPPORTED for systems without network support.
 */
BCL_STATUS RegisterUdpEndpoint (
    ServiceMaster *         serviceMaster,
    UdpHandle               handle,
    struct sockaddr_in      dest_addr
);

/**
 * @brief Send packet over the serial port bound to the ServiceMaster.
 *
 * @param serviceMaster     ServiceMaster struct
 * @param pkt               Packet to send
 * @return BCL_OK on success.
 */
BCL_STATUS SendPacketOverSerial (
    ServiceMaster *         serviceMaster,
    BclPacket *             pkt
);

/**
 * @brief Send packet over the serial port bound to the ServiceMaster.
 *
 * @param serviceMaster     ServiceMaster struct
 * @param pkt               Packet to send
 * @param dest_addr         Destination address to send the packet.
 * @return BCL_OK on success.
 */
BCL_STATUS SendPacketOverUdp (
    ServiceMaster *         serviceMaster,
    BclPacket *             pkt,
    struct sockaddr_in      dest_addr
);

BCL_STATUS HandleControlServicePacket (
    ServiceMaster *         serviceMaster,
    BclPacketHeader *       header
);

/**
 * @brief Starts the main execution loop of the ServiceMaster.
 *
 * Does not return.
 *
 * @param serviceMaster     ServiceMaster struct
 * @return void
 */
void RunServiceMaster(
    ServiceMaster *     serviceMaster
); 
#endif