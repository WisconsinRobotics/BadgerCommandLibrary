#include "Net.h"


UdpHandle OpenUdpPort (
    int port
    )
{
    UdpHandle handle;
    struct sockaddr_in addr;

    handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle == INVALID_UDP_HANDLE)
        return INVALID_UDP_HANDLE;

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (bind(handle, (struct sockaddr *) &socket_addr, sizeof(struct sockaddr)) == -1)
        return INVALID_UDP_HANDLE;

    return handle;
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
    socklen_t from_sz;

    if (!buffer || handle == INVALID_UDP_HANDLE || !from)
        return BCL_INVALID_PARAMETER;

    from_sz = sizeof(struct sockaddr);
    read = recvfrom(socket, buffer, size, 0, from, &from_sz);
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
    close(handle);
}