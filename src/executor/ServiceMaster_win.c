#include "ServiceMaster.h"
#include "Service.h"
#include "Serial.h"
#include "Net.h"
#include <windows.h>

char SerialIncomingBuffer[256];
char UdpIncomingBuffer[256];

static void PacketDispatcher(
    ServiceMaster *         serviceMaster,
    uint8_t *               buffer,
    int                     length,
    LastPacketInterface     lpinterface,
    struct sockaddr_in *    addr
)
{
    for (int i = 0; i < MAX_SUBSYSTEMS; i++)
    {
        Subsystem *subsystem = serviceMaster->Subsystems[i];
        if (!BIT_SET(subsystem->_allocated_bitset, i))
            continue;

        for (int j = 0; j < MAX_SERVICES_PER_SUBSYSTEM; j++)
        {
            Service *service = subsystem->Services[i];

            // skip if not allocated
            if (!BIT_SET(subsystem->_allocated_bitset, i))
                continue;

            // if service is not a run on packet
            if (service->SleepInterval != RUN_ON_PACKET_RECEIVE)
                continue;

            // if the handler isn't defined
            if (!service->HandlePacket)
                continue;

            // if parse ok - update origin interface info
            BCL_STATUS status = (*(service->HandlePacket))(service, buffer, length);
            if (status == BCL_OK)
            {
                service->LastPacketOrigin.Interface = lpinterface;
                if (addr)
                    service->LastPacketOrigin.SourceAddr = *addr;
                return;
            }
        }
    }
}

static DWORD WINAPI SerialReadThread (
    LPVOID *            param
    )
{
    ServiceMaster *serviceMaster = (ServiceMaster *) param;
    SerialHandle handle = serviceMaster->SerialPort;

    while (TRUE)
    {
        BCL_STATUS status;
        int bytes_read;

        memset(SerialIncomingBuffer, 0, 256);
        status = SerialPortReadData(handle, SerialIncomingBuffer, 256, &bytes_read);
        if (status == BCL_SERIAL_ERROR)
            continue;
        
        PacketDispatcher(serviceMaster, SerialIncomingBuffer, 256, LPI_SERIAL, NULL);
    }

    return 0;
}

static DWORD WINAPI UdpReadThread (
    LPVOID *            param
    )
{
    ServiceMaster *serviceMaster = (ServiceMaster *)param;
    UdpHandle handle = serviceMaster->UdpPort;
    struct sockaddr_in rec_addr;

    memset(&rec_addr, 0, sizeof(struct sockaddr_in));

    while (TRUE)
    {
        BCL_STATUS status;
        int bytes_read;

        memset(UdpIncomingBuffer, 0, 256);
        status = UdpPortReadData(handle, UdpIncomingBuffer, 256, &rec_addr, &bytes_read);
        if (status == BCL_SOCKET_ERROR)
            continue;

        PacketDispatcher(serviceMaster, UdpIncomingBuffer, 256, LPI_UDP, &rec_addr);
    }

    return 0;
}

static void CALLBACK ServiceExecutorThreadCallback (
    PVOID   lpParameter,
    BOOLEAN TimerOrWaitFired
    )
{
    // iterate over each service
}

void RunServiceMaster(
    ServiceMaster *     serviceMaster
    )
{
    HANDLE serialReadHandle = INVALID_HANDLE_VALUE;
    HANDLE udpReadHandle = INVALID_HANDLE_VALUE;

    if (!serviceMaster)
        return;

    // ensure that at least one interface is open
    if (serviceMaster->SerialPort != INVALID_SERIAL_HANDLE)
        serialReadHandle = CreateThread(NULL, 0, SerialReadThread, serviceMaster, 0, NULL);

    if (serviceMaster->UdpPort != INVALID_UDP_HANDLE)
        udpReadHandle = CreateThread(NULL, 0, UdpReadThread, serviceMaster, 0, NULL);

    // no interface open, quit
    if (serialReadHandle == INVALID_HANDLE_VALUE && udpReadHandle == INVALID_HANDLE_VALUE)
        return;

    // set up timer
    // CreateTimerQueue

    // determine min freq to run
    // note: need to keep track of last time executed
    // 
}
