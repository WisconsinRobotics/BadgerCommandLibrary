#pragma once

#include "Service.hpp"
#include "UdpSocket.hpp"
#include "Serial.hpp"
#include "Timer.hpp"
#include "Packet.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <thread>


namespace BCL
{
    class Service;

    // note: should we unify the SendPacket* methods and robotEndpointMap?
    // i.e. should ServiceMaster autodetect what interface to use based on dest. robot id?

    class ServiceMaster
    {
    public:
        ServiceMaster(int robot_id);
        ~ServiceMaster();
        void InitUdpPort(int port = 0);
        void InitSerialPort(std::string portname, int baud);
        uint8_t GetRobotID() const;
        void AddService(Service *s);
        void AddEndpoint(int robot_id, struct sockaddr_in addr);
        bool Run();
        void Stop();
        BCL_STATUS SendPacketSerial(BclPacket *pkt);
        int SendBufferSerial(uint8_t *buffer, int length);
        BCL_STATUS SendPacketUdp(BclPacket *pkt);
        int SendBufferUdp(uint8_t *buffer, int length, int destID);

    private:
        void SerialReader();
        void UdpSocketReader();
        void PacketHandler(const uint8_t *buffer, uint8_t length);

        uint8_t robotID;
        std::unique_ptr<UdpSocket> socket;
        std::unique_ptr<SerialPort> serialPort;
        std::vector<Service *> services;
        std::map<int, struct sockaddr_in> robotEndpointMap;
        std::chrono::milliseconds timer_interval;
        std::thread serialReadThread;
        std::thread udpReadThread;
        bool isRunning;
    };
}