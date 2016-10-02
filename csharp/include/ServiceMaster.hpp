#pragma once

#include "Service.hpp"
#include "Serial.hpp"
#include "SerialPort.hpp"

using System::Collections::Generic::List;
using System::Collections::Generic::Dictionary;
using System::Net::IPEndPoint;
using System::Net::Sockets::UdpClient;
using System::Threading::Thread;
using System::Threading::ThreadStart;

namespace BclSharp
{
    ref class Service;

    public ref class ServiceMaster
    {
        // note: should we unify the SendPacket* methods and robotEndpointMap?
        // i.e. should ServiceMaster autodetect what interface to use based on dest. robot id?

        public:
            ServiceMaster(int robot_id, UdpClient^ udpClient, SerialPort^ serialPort);
            ~ServiceMaster();
            System::Int32 GetRobotID();
            void AddService(Service^ s);
            void AddEndpoint(int robot_id, IPEndPoint^ addr);
            void Run();
            void SendPacketSerial(Packet^ pkt);
            void SendPacketUdp(Packet^ pkt);

        private:
            void SerialReader();
            void UdpSocketReader();
            void PacketHandler(array<System::Byte>^ buffer);

            int robotID;
            UdpClient ^socket;
            SerialPort ^serialPort;
            List<Service^>^ services;
            Dictionary<System::Int32, IPEndPoint^>^ robotEndpointMap;
            System::Int32 timer_interval;
            bool isRunning;
    };
}