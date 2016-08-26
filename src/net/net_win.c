#include "Net.h"

#pragma comment(lib, "Ws2_32.lib")


UdpHandle OpenUdpPort (
    int port
    )
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in socket_addr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return INVALID_UDP_HANDLE;

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        WSACleanup();
        return INVALID_UDP_HANDLE;
    }

    memset(&socket_addr, 0, sizeof(struct sockaddr_in));
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &socket_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
    {
        WSACleanup();
        return INVALID_UDP_HANDLE;
    }

    return sock;
}

BCL_STATUS UdpPortWriteData (
    UdpHandle handle,
    struct sockaddr_in addr,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
    )
{
    uint8_t written;

    if (!buffer || handle == INVALID_UDP_HANDLE)
        return BCL_INVALID_PARAMETER;

    written = sendto(handle, buffer, length, 0, (struct sockaddr *) &addr, sizeof(struct sockaddr));
    if (written < 0)
        return BCL_SOCKET_ERROR;

    if (bytes_written)
        *bytes_written = written;

    return BCL_OK;
}

BCL_STATUS UdpPortReadData (
    UdpHandle handle,
    void *buffer,
    uint8_t length,
    struct sockaddr *from,
    uint8_t *bytes_read
    )
{
    uint8_t read;
    int from_sz;

    if (!buffer || handle == INVALID_UDP_HANDLE || !from)
        return BCL_INVALID_PARAMETER;

    from_sz = sizeof(struct sockaddr);
    read = recvfrom(handle, buffer, length, 0, from, &from_sz);
    if (read < 0)
        return BCL_SOCKET_ERROR;

    if (bytes_read)
        *bytes_read = read;

    return BCL_OK;
}

void CloseUdpPort (
    UdpHandle handle
    )
{
    if (handle != INVALID_UDP_HANDLE)
    {
        closesocket(handle);
        WSACleanup();
    }
}