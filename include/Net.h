#ifndef _NET_H
#define _NET_H

#if defined(_WIN32) || defined(__linux__)
#define NETWORK_SUPPORTED 1
#endif

#include "BclConfig.h"
#include "BclStatus.h"
#include <stdint.h>


#ifdef _WIN32
    #include <windows.h>
    typedef SOCKET UdpHandle;
#elif defined(__linux__)
    #include <arpa/inet.h>
    #include <sys/socket.h>
    typedef unsigned int UdpHandle;
#else
    typedef unsigned int UdpHandle;
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