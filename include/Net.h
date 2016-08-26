#ifndef _NET_H
#define _NET_H

#include "BclConfig.h"
#include "BclStatus.h"


#ifdef _WIN32
    #include <windows.h>
    #define UdpHandle HANDLE
#else
    #define UdpHandle int
#endif

#define INVALID_UDP_HANDLE ((UdpHandle)(-1))

UdpHandle OpenUdpPort (
    int port
);

BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
);

BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t size,
    uint8_t *bytes_read
);

void CloseSerialPort (
    UdpHandle handle
);


#endif