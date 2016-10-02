#pragma once

#include "Service.hpp"
#include "UdpSocket.hpp"
#include "Serial.hpp"
#include "Timer.hpp"
#include "Packet.h"
#include <vector>
#include <map>


namespace BCL
{
    class Service;

    // note: should we unify the SendPacket* methods and robotEndpointMap?
    // i.e. should ServiceMaster autodetect what interface to use based on dest. robot id?

    class ServiceMaster
    {
    public:
        ServiceMaster(int robot_id, UdpSocket *udpSocket, SerialPort *serialPort);
        ~ServiceMaster();
        int GetRobotID();
        void AddService(Service *s);
        void AddEndpoint(int robot_id, struct sockaddr_in addr);
        void Run();
        BCL_STATUS SendPacketSerial(BclPacket *pkt);
        BCL_STATUS SendPacketUdp(BclPacket *pkt);

    private:
        void SerialReader();
        void UdpSocketReader();
        void PacketHandler(const uint8_t *buffer, int length);

        int robotID;
        UdpSocket *socket;
        SerialPort *serialPort;
        std::vector<Service *> services;
        std::map<int, struct sockaddr_in> robotEndpointMap;
        std::chrono::milliseconds timer_interval;
        bool isRunning;
    };
}