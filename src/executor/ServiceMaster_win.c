#include "ServiceMaster.h"
#include "Service.h"
#include "Serial.h"
#include "Net.h"
#include <windows.h>

char SerialIncomingBuffer[255];
char UdpIncomingBuffer[255];

static void PacketDispatcher(
    ServiceMaster *         serviceMaster,
    uint8_t *               buffer,
    int                     length
    )
{

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
        uint8_t bytes_read;

        memset(SerialIncomingBuffer, 0, 255);
        status = SerialPortReadData(handle, SerialIncomingBuffer, 255, &bytes_read);
        if (status == BCL_SERIAL_ERROR)
            continue;
        
        PacketDispatcher(serviceMaster, SerialIncomingBuffer, 255);
    }

    return 0;
}

static DWORD WINAPI UdpReadThread (
    LPVOID *            param
    )
{
    ServiceMaster *serviceMaster = (ServiceMaster *)param;
    UdpHandle handle = serviceMaster->UdpPort;

    while (TRUE)
    {
        BCL_STATUS status;
        uint8_t bytes_read;

        memset(UdpIncomingBuffer, 0, 255);
        status = UdpPortReadData(handle, UdpIncomingBuffer, 255, NULL, &bytes_read);
        if (status == BCL_SOCKET_ERROR)
            continue;

        PacketDispatcher(serviceMaster, UdpIncomingBuffer, 255);
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
