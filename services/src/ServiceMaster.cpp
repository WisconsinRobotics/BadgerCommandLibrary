#include "ServiceMaster.hpp"
#include "Service.hpp"
#include <cstdint>

using namespace BCL;

constexpr int READ_BUFFER_SIZE = 256;

ServiceMaster::ServiceMaster(int port) : socket(port)
{
    this->isRunning = false;
}

ServiceMaster::~ServiceMaster()
{
}

void ServiceMaster::AddService(Service *s)
{
    this->services.push_back(s);
    if (this->isRunning)
        s->ExecuteOnTime();
}

void ServiceMaster::AddEndpoint(int robot_id, struct sockaddr_in addr)
{
    this->robotEndpointMap[robot_id] = addr;
}

BCL_STATUS ServiceMaster::SendPacket(BclPacket *pkt)
{
    uint8_t buffer[255];
    uint8_t bytes_written;
    BCL_STATUS status;

    if (pkt == nullptr)
        return BCL_INVALID_PARAMETER;
    
    status = SerializeBclPacket(pkt, buffer, 255, &bytes_written);
    if (status != BCL_OK)
        return status;

    int robot_id = pkt->Header.Destination.RobotID;
    if (this->robotEndpointMap.find(robot_id) == this->robotEndpointMap.end())
        return BCL_NOT_FOUND;

    struct sockaddr_in dest_addr = this->robotEndpointMap[robot_id];

    this->socket.Write(buffer, bytes_written, (struct sockaddr *) &dest_addr);
    return BCL_OK;
}

void ServiceMaster::Run()
{
    uint8_t read_buffer[READ_BUFFER_SIZE];

    if (!socket.Open())
        return;

    // run the services
    for (auto& s : this->services)
        if (s->GetSleepInterval() == Service::RUN_ON_PACKET_RECEIVE)
            s->ExecuteOnTime();

    memset(read_buffer, 0, READ_BUFFER_SIZE);

    while (true)
    {
        struct sockaddr_in src_addr;
        int bytes_read = socket.Read(read_buffer, READ_BUFFER_SIZE, (struct sockaddr *) &src_addr);
        if (bytes_read < 0)
            continue;

        // TODO: account for broken packets across reads
        // past experience has shown that this does happen occasionally, but usually nothing to worry about

        bool src_addr_found = false;
        for (auto it : robotEndpointMap)
        {
            // TODO:
            // compare addresses to see if found
            // if not, add it
        }

        for (auto& s : this->services)
        {
            if (!s->IsActive())
                continue;

            if (!s->HandlePacket(read_buffer, bytes_read))
                continue;

            if (s->GetSleepInterval() == Service::RUN_ON_PACKET_RECEIVE)
                s->ExecuteOnTime();

            // packet issued to service - continue reading
            break;
        }
    }
}
