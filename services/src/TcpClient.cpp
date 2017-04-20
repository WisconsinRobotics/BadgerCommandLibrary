#include "TcpClient.hpp"

using namespace BCL;


TcpClient::TcpClient(int port)
{
    this->port = port;
    this->isOpen = false;
    this->connected = false;
    memset(&other_endpoint_addr, 0, sizeof(struct sockaddr));
    handle = INVALID_SOCKET_HANDLE;
    other_endpoint_handle = INVALID_SOCKET_HANDLE;
    listener = false;
}

TcpClient::~TcpClient()
{
    if (this->isOpen)
    {
        this->Close();
#ifdef _WIN32
        WSACleanup();
#endif
    }
}

bool TcpClient::Open()
{
    _socket_t sock_handle;
    struct sockaddr_in addr;

    if (this->isOpen || this->connected)
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

    sock_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_handle == INVALID_SOCKET_HANDLE)
        OPEN_FAIL();

    memset(&addr, 0, sizeof(struct sockaddr_in));
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

bool TcpClient::IsOpen() const
{
    return this->isOpen;
}

bool TcpClient::Listen()
{
    if (!this->isOpen || this->connected)
        return true;

    if (listen(this->handle, 0) != 0)
        return false;

    socklen_t client_addr_sz = sizeof(struct sockaddr);
    this->other_endpoint_handle = accept(this->handle, (struct sockaddr *)&this->other_endpoint_addr, &client_addr_sz);

    bool success = this->other_endpoint_handle != INVALID_SOCKET_HANDLE;
    if (success)
        this->connected = true;

    listener = true;
    return success;
}

bool TcpClient::Connect(struct sockaddr_in dest)
{
    if (!this->isOpen || this->connected)
        return true;

    this->other_endpoint_addr = dest;
    bool success = connect(this->handle, (struct sockaddr *)&this->other_endpoint_addr, sizeof(struct sockaddr)) == 0;
    if (success)
        this->connected = true;
    return success;
}

bool TcpClient::IsConnected() const
{
    return this->connected;
}

void TcpClient::Close()
{
    if (!this->isOpen)
        return;

#ifdef _WIN32
    #define close(socket) closesocket(socket)
#endif
    if (this->handle != INVALID_SOCKET_HANDLE)
        close(this->handle);

    if (this->other_endpoint_handle != INVALID_SOCKET_HANDLE)
        close(this->other_endpoint_handle);
#undef close

    this->connected = false;
}

int TcpClient::Write(const void * buffer, unsigned int size)
{
    if (!this->isOpen || !this->connected)
        return -1;
    return send((listener) ? this->other_endpoint_handle : this->handle, (const char *)buffer, size, 0);
}

int TcpClient::Read(void * buffer, unsigned int size)
{
    if (!this->isOpen || !this->connected)
        return -1;
    return recv((listener) ? (this->other_endpoint_handle) : this->handle, (char *)buffer, size, 0);
}

int TcpClient::GetPort() const
{
    return this->port;
}
