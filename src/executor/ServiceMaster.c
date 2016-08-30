#include <string.h>
#include "BclConfig.h"
#include "ServiceMaster.h"
#include "Serial.h"
#include "Net.h"

BCL_STATUS InitializeServiceMaster (
    ServiceMaster *     serviceMaster
    )
{
    if (serviceMaster == NULL)
        return BCL_INVALID_PARAMETER;

    memset(serviceMaster, 0, sizeof(ServiceMaster));
    serviceMaster->SerialPort = INVALID_SERIAL_HANDLE;
    serviceMaster->UdpPort = INVALID_UDP_HANDLE;
    return BCL_OK;
}

BCL_STATUS BclRegisterService(
    ServiceMaster *     serviceMaster,
    Service *           service
)
{
    if (!serviceMaster || !service)
        return BCL_INVALID_PARAMETER;

    // find a free spot, and assign
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        if (serviceMaster->Services[i] == NULL)
        {
            serviceMaster->Services[i] = service;
            return BCL_OK;
        }
    }

    return BCL_OUT_OF_RESOURCES;
}

BCL_STATUS RegisterSerialPort (
    ServiceMaster *     serviceMaster,
    SerialHandle        handle
    )
{
    if (!serviceMaster || handle == INVALID_SERIAL_HANDLE)
        return BCL_INVALID_PARAMETER;

    serviceMaster->SerialPort = handle;
    return BCL_OK;
}

BCL_STATUS RegisterUdpEndpoint (
    ServiceMaster *     serviceMaster,
    UdpHandle           handle,
    struct sockaddr_in  dest_addr
    )
{
    if (!serviceMaster || handle == INVALID_UDP_HANDLE)
        return BCL_INVALID_PARAMETER;

    serviceMaster->UdpPort = handle;
    serviceMaster->UdpEndpoint = dest_addr;
    
    return BCL_OK;
}

BCL_STATUS SendPacketOverSerial (
    ServiceMaster *     serviceMaster,
    BclPacket *            pkt
    )
{
    uint8_t buffer[MAX_PACKET_SIZE];
    uint8_t pkt_size;
    BCL_STATUS status;

    status = SerializeBclPacket(pkt, buffer, MAX_PACKET_SIZE, &pkt_size);
    if (status != BCL_OK)
        return status;

    // no valid handle found
    if (serviceMaster->SerialPort == INVALID_SERIAL_HANDLE)
        return BCL_NOT_FOUND;

    return SerialPortWriteData (
        serviceMaster->SerialPort,
        buffer,
        MAX_PACKET_SIZE, 
        NULL
    );
}

BCL_STATUS SendPacketOverUdp (
    ServiceMaster *     serviceMaster,
    BclPacket *            pkt,
    struct sockaddr_in     dest_addr
    )
{
#if NETWORK_SUPPORTED
    uint8_t buffer[MAX_PACKET_SIZE];
    uint8_t pkt_size;
    BCL_STATUS status;

    status = SerializeBclPacket(pkt, buffer, MAX_PACKET_SIZE, &pkt_size);
    if (status != BCL_OK)
        return status;

    // no valid handle found
    if (serviceMaster->UdpPort == INVALID_UDP_HANDLE)
        return BCL_NOT_FOUND;

    return UdpPortWriteData (
        serviceMaster->UdpPort,
        dest_addr,
        buffer,
        MAX_PACKET_SIZE, 
        NULL
    );
#else
    return BCL_UNSUPPORTED;
#endif
}