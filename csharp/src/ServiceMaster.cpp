#include "ServiceMaster.hpp"
#include "Service.hpp"
#include <cstdint>

using namespace BclSharp;

constexpr int READ_BUFFER_SIZE = 256;

ServiceMaster::ServiceMaster(int robot_id, UdpClient^ udpClient, SerialPort^ serialPort)
{
    this->robotID = robot_id;
    this->isRunning = false;

    this->socket = udpClient;
    this->serialPort = serialPort;
}

ServiceMaster::~ServiceMaster()
{
}

int ServiceMaster::GetRobotID()
{
    return this->robotID;
}

void ServiceMaster::AddService(Service ^s)
{
    this->services->Add(s);
    
    s->SetServiceMaster(this);
    if (this->isRunning)
        s->ExecuteOnTime();
}

void ServiceMaster::AddEndpoint(int robot_id, IPEndPoint^ addr)
{
    this->robotEndpointMap[robot_id] = addr;
}

void ServiceMaster::SendPacketSerial(Packet^ pkt)
{
    uint8_t buffer[255];
    uint8_t bytes_written;

    if (pkt == nullptr || this->serialPort == nullptr)
        return;

    array<System::Byte>^ data = pkt->Serialize();
    this->serialPort->Write(data, data->Length);
}

void ServiceMaster::SendPacketUdp(Packet^ pkt)
{
    uint8_t buffer[255];
    uint8_t bytes_written;
    BCL_STATUS status;

    if (pkt == nullptr || this->socket == nullptr)
        return;

    array<System::Byte>^ data = pkt->Serialize();

    int robot_id = pkt->Destination->RobotID;
    if (!this->robotEndpointMap->ContainsKey(robot_id))
        return;

    IPEndPoint^ dest_addr = this->robotEndpointMap[robot_id];
    this->socket->Send(data, data->Length, dest_addr);
}

void ServiceMaster::SerialReader()
{
    array<System::Byte>^ read_buffer = gcnew array<System::Byte>(READ_BUFFER_SIZE);

    while (true)
    {
        int bytes_read = this->serialPort->Read(read_buffer, READ_BUFFER_SIZE);
        if (bytes_read < 0)
            continue;

        this->PacketHandler(read_buffer);
    }
}

void ServiceMaster::UdpSocketReader()
{
    while (true)
    {
        IPEndPoint^ src_addr = gcnew IPEndPoint(System::Net::IPAddress::Any, 0);
        array<System::Byte>^ read_buffer = socket->Receive(src_addr);
        if (read_buffer->Length < 0)
            continue;

        // TODO: if packet received is from unknown address, but is valid
        // add to robotEndpointMap

        this->PacketHandler(read_buffer);
    }
}

void ServiceMaster::PacketHandler(array<System::Byte>^ buffer)
{
    // TODO: handle access control packets here

    for each (Service^ s in this->services)
    {
        if (!s->IsActive)
            continue;

        if (!s->HandlePacket(buffer, buffer->Length))
            continue;

        if (s->SleepInterval == Service::RUN_ON_PACKET_RECEIVE)
            s->ExecuteOnTime();

        // packet issued to service - done!
        return;
    }
}

void ServiceMaster::Run()
{
    Thread^ serialReadThread = gcnew Thread(gcnew ThreadStart(this, &ServiceMaster::SerialReader));
    Thread^ udpReadThread =  gcnew Thread(gcnew ThreadStart(this, &ServiceMaster::UdpSocketReader));

    // run the services
    for each (Service^ s in this->services)
        if (s->SleepInterval != Service::RUN_ON_PACKET_RECEIVE)
            s->ExecuteOnTime();

    if (this->serialPort)
        serialReadThread->Start();

    if (this->socket)
        udpReadThread->Start();

    while (true);
}
