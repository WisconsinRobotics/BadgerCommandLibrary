#pragma once

#include <functional>
#include <cstring>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <WS2tcpip.h>
    #include <windows.h>
    #pragma comment(lib, "Ws2_32.lib")
    typedef SOCKET _socket_t;
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
    typedef int  _socket_t;
#endif

constexpr _socket_t INVALID_SOCKET_HANDLE = (_socket_t) -1;

namespace BCL
{
    class TcpClient
    {
    public:
        TcpClient(int port = 0);
        ~TcpClient();

        /* Initializes the TcpClient instance */
        bool Open();
        bool IsOpen() const;

        /* Listens for an incoming connection */
        bool Listen();

        /* Connects to an existing TCP server */
        bool Connect(struct sockaddr_in dest);
        bool IsConnected() const;

        /* Closes the connection, if there is one */
        void Close();

        int Write(const void *buffer, unsigned int size);
        int Read(void *buffer, unsigned int size);
        int GetPort() const;

    private:
        struct sockaddr_in other_endpoint_addr;
        int port;
        _socket_t handle;
        _socket_t other_endpoint_handle;
        bool isOpen;
        bool connected;
        bool listener;
    }; 
}



