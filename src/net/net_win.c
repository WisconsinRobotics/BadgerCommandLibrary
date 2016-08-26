#include "Net.h"
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")


UdpHandle OpenUdpPort (
    int port
    )
{
    WSADATA wsaData;
    SOCKET socket;
    struct sockaddr_in socket_addr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return INVALID_UDP_HANDLE;

    socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket == INVALID_SOCKET)
    {
        WSACleanup();
        return INVALID_UDP_HANDLE;
    }

    memset(&socket_addr, 0, sizeof(struct sockaddr_in));
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);

    if (bind(socket, (struct sockaddr *) &socket_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
    {
        WSACleanup();
        return INVALID_UDP_HANDLE;
    }

    return socket;
}

BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    struct sockaddr_in addr,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
    )
{
    uint8_t written;

    if (!buffer || handle == INVALID_UDP_HANDLE)
        return BCL_INVALID_PARAMETER;

    written = sendto(handle, buffer, size, 0, (struct sockaddr *) addr, sizeof(struct sockaddr));
    if (written < 0)
        return BCL_SOCKET_ERROR;

    if (bytes_written)
        *bytes_written = written;

    return BCL_OK;
}

BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t size,
    struct sockaddr *from,
    uint8_t *bytes_read
    )
{
    uint8_t read;

    if (!buffer || handle == INVALID_UDP_HANDLE || !from)
        return BCL_INVALID_PARAMETER;

    read = recvfrom(socket, buffer, size, 0, from, sizeof(struct sockaddr));
    if (read < 0)
        return BCL_SOCKET_ERROR;

    if (bytes_read)
        *bytes_read = read;

    return BCL_OK;
}

void CloseSerialPort (
    UdpHandle handle
    )
{
    if (handle != INVALID_UDP_HANDLE)
    {
        closesocket(handle);
        WSACleanup();
    }
}