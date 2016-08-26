#ifndef _NET_H
#define _NET_H

#include "BclConfig.h"
#include "BclStatus.h"
#include <stdint.h>


#ifdef _WIN32
    #include <windows.h>
    #define UdpHandle SOCKET
#else
    #define UdpHandle int
#endif

#ifndef NETWORK_SUPPORTED
typedef struct sockaddr_in int;
typedef struct sockaddr int;
#endif

#define INVALID_UDP_HANDLE ((UdpHandle)(-1))


UdpHandle OpenUdpPort (
    int port
);

BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    struct sockaddr_in addr,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
);

BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t length,
    struct sockaddr *from,
    uint8_t *bytes_read
);

void CloseUdpPort (
    UdpHandle handle
);


#endif