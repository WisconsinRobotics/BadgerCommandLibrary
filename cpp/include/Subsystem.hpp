#pragma once

#include "Service.hpp"

#ifdef __AVR__
#include "avr/Subsystem.hpp"
#else

#include <vector>

namespace BCL
{
    class Subsystem
    {
    public:
        Subsystem(int id);
        ~Subsystem(void);
        const std::vector<Service>& GetServices(void);
        const Service& GetService(int serviceID);
        void RemoveService(int serviceID);
        void AddService(Service& service);
    private:
        std::vector<Service> services;
    };
}

#endif
