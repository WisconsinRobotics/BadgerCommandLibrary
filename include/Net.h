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

/**
 * @brief Opens and returns a handle to a bound socket on the specified port.
 *
 * @param port The port to open
 * @return A UdpHandle to the bound socket, INVALID_UDP_HANDLE on failure.
 */
UdpHandle OpenUdpPort (
    int port
);

/**
 * @brief Writes the specified data using the specified handle.
 * 
 * @param handle        A handle to a UDP socket.
 * @param addr          The destination address.
 * @param buffer        The buffer to write.
 * @param length        The length of the buffer.
 * @param bytes_written An optional pointer that reports how many bytes were actually written.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    struct sockaddr_in addr,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
);

/**
 * @brief Reads data from the UDP socket.
 * 
 * @param handle        A handle to a UDP socket.
 * @param buffer        The buffer to write.
 * @param length        The length of the buffer.
 * @param from          An optional pointer that holds where the data originated.
 * @param bytes_read    An optional pointer that reports how many bytes were actually read.
 *
 * @return BCL_OK on success.
 */
BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t length,
    struct sockaddr *from,
    uint8_t *bytes_read
);

/**
 * @brief Closes the specified UDP socket.
 *
 * @param handle        An open handle to a UDP socket.
 * @return void
 */
void CloseUdpPort (
    UdpHandle handle
);

#endif