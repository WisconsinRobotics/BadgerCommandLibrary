#pragma once

#include "Subsystem.hpp"
#include "Service.hpp"

#ifdef __AVR__
    #include "avr/ServiceMaster.hpp"
#else

#include <thread>
#include <vector>

namespace BCL
{
    class ServiceMaster
    {
    public:
        ServiceMaster(void);
        ~ServiceMaster(void);
        bool OpenSerialPort(const char *port, int baudrate);
        bool OpenUdpPort(int port);

    private:

    };
}
#endif