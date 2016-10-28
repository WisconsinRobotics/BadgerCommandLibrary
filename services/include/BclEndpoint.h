#pragma once

#include "UdpSocket.hpp"
#include "Serial.hpp"

namespace BCL
{
    class BclEndpoint
    {
    public:
        BclEndpoint(int robot_id, bool serial, void *addr);
        ~BclEndpoint();
		Write(void *buff);
		Read(void *buff);
    private:
		int robot_id;
        bool serial;
		struct sockaddr_in *addr;
		BCL::UdpSocket *sock;
		BCL::SerialPort *port;
    };
}