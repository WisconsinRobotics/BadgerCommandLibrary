#include "Net.h"


UdpHandle OpenUdpPort (
    int port
    )
{
    return INVALID_UDP_HANDLE;
}

BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    struct sockaddr_in addr,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
    )
{
    return BCL_UNSUPPORTED;
}

BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t size,
    struct sockaddr *from,
    uint8_t *bytes_read
    )
{
    return BCL_UNSUPPORTED;
}

void CloseSerialPort (
    UdpHandle handle
    )
{
}