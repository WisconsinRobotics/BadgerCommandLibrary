#pragma once

#include "Service.hpp"
#include "UdpSocket.hpp"
#include "Timer.hpp"
#include "Packet.h"
#include <vector>
#include <map>


namespace BCL
{
    class Service;

    // TODO: Support multiple interfaces
    class ServiceMaster
    {
    public:
        ServiceMaster(int robot_id, int port);
        ~ServiceMaster();
        int GetRobotID();
        void AddService(Service *s);
        void AddEndpoint(int robot_id, struct sockaddr_in addr);
        void Run();
        BCL_STATUS SendPacket(BclPacket *pkt);

    private:
        UdpSocket socket;
        int robotID;
        std::vector<Service *> services;
        std::map<int, struct sockaddr_in> robotEndpointMap;
        std::chrono::milliseconds timer_interval;
        bool isRunning;
    };
}