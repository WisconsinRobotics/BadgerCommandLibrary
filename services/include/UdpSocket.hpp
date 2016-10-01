#pragma once

#ifdef _WIN32
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


namespace BCL
{
    class UdpSocket
    {
    public:
        UdpSocket(int port = 0);
        ~UdpSocket();
        bool Open();
        bool IsOpen() const;
        void Close();
        int Write(const void *buffer, unsigned int size, struct sockaddr *dest_addr);
        int Read(void *buffer, unsigned int size, struct sockaddr *source_addr);
        int GetPort() const;
        
    private:
        struct sockaddr socket_addr;
        int port;
        _socket_t handle;
        bool isOpen;
    };
}