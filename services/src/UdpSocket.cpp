#include "UdpSocket.hpp"
#include <cstring>

using namespace BCL;

constexpr _socket_t INVALID_SOCKET_HANDLE = ((_socket_t)(-1));

UdpSocket::UdpSocket(int port)
{
    this->port = port;
    this->isOpen = false;
}

UdpSocket::~UdpSocket()
{
    if (this->isOpen)
        this->Close();
}

bool UdpSocket::Open()
{
    _socket_t sock_handle;
    struct sockaddr_in addr;

    if (this->isOpen)
        return true;
    
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return false;
#endif

#ifdef _WIN32
    #define OPEN_FAIL() { WSACleanup(); return false; }
#else
    #define OPEN_FAIL() { return false; }
#endif

    sock_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_handle == INVALID_SOCKET_HANDLE)
        OPEN_FAIL();

    std::memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<u_short>(port));

    if (bind(sock_handle, (struct sockaddr *) &addr, sizeof(struct sockaddr)) != 0)
        OPEN_FAIL();

    this->handle = sock_handle;
    this->isOpen = true;
    return true;
    #undef OPEN_FAIL
}

void UdpSocket::Close()
{
    if (!this->isOpen)
        return;

    this->isOpen = false;
    #ifdef _WIN32
    closesocket(handle);
    #else
    close(handle);
    #endif
}

int UdpSocket::Write(const void *buffer, unsigned int size, struct sockaddr *dest_addr)
{
    if (buffer == nullptr || dest_addr == nullptr)
        return -1;
    
    return sendto(handle, (const char *)buffer, size, 0, dest_addr, sizeof(struct sockaddr));
}

int UdpSocket::Read(void *buffer, unsigned int size, struct sockaddr *source_addr)
{
    socklen_t source_addr_size;

    if (buffer == nullptr)
        return -1;

    source_addr_size = sizeof(struct sockaddr);
    if (source_addr)
        return recvfrom(handle, (char *)buffer, size, 0, source_addr, &source_addr_size);
    else
        return recvfrom(handle, (char *)buffer, size, 0, nullptr, nullptr);
}

int UdpSocket::GetPort() const
{
    return port;
}

bool UdpSocket::IsOpen() const
{
    return this->isOpen;
}