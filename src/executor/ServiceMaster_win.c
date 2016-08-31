#include "ServiceMaster.h"
#include "Packet.h"
#include "Service.h"
#include "Serial.h"
#include "Net.h"
#include <windows.h>
#include <stdio.h>

char SerialIncomingBuffer[255];
char UdpIncomingBuffer[255];


static BOOL PacketDispatcher(
    ServiceMaster *         serviceMaster,
    uint8_t *               buffer,
    int                     length
    )
{
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        Service *s = serviceMaster->Services[i];
        if (!s)
            continue;

        if (!s->Active)
            continue;

        if (!s->HandlePacket)
            continue;

        BCL_STATUS status = (*s->HandlePacket)(s, buffer, length);
        if (status != BCL_OK)
            continue;

        // if the service executes only when packets come in, then run it
        if (s->SleepInterval == RUN_ON_PACKET_RECEIVE && s->Execute)
            (*s->Execute)(s);

        // packet handled - we're done
        return TRUE;
    }

    return FALSE;
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
        
        BOOL dispatchSuccess = PacketDispatcher(serviceMaster, SerialIncomingBuffer, 255);
        if (!dispatchSuccess)
            printf("Failed to dispatch serial packet with opcode 0x%x\n", SerialIncomingBuffer[OPCODE_INDEX]);
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

        BOOL dispatchSuccess = PacketDispatcher(serviceMaster, UdpIncomingBuffer, 255);
        if (!dispatchSuccess)
            printf("Failed to dispatch UDP packet with opcode 0x%x\n", UdpIncomingBuffer[OPCODE_INDEX]);
    }

    return 0;
}

static inline double diffclock (
    clock_t clock1, 
    clock_t clock2
    )
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
    return diffms;
}

static void CALLBACK ServiceExecutorThreadCallback (
    PVOID   lpParameter,
    BOOLEAN TimerOrWaitFired
    )
{
    ServiceMaster *serviceMaster = (ServiceMaster *)lpParameter;

    for (int i = 0; i < MAX_SERVICES; i++)
    {
        Service *s = serviceMaster->Services[i];
        if (!s || !s->Active)
            continue;

        // ignore event-based services
        if (s->SleepInterval == RUN_ON_PACKET_RECEIVE)
            continue;

        // check if service needs to be run
        clock_t last_run = s->LastTimeRun;
        clock_t current = clock();

        if (diffclock(current, last_run) > s->SleepInterval)
        {
            s->LastTimeRun = current;
            if (s->Execute)
                (*s->Execute)(s);
        }
    }
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

    // determine min period to run
    clock_t min_period;
    BOOL min_period_initialized = FALSE;
    BOOL at_least_one_service_exists = FALSE;

    for (int i = 0; i < MAX_SERVICES; i++)
    {
        Service *s = serviceMaster->Services[i];
        if (!s)
            continue;

        at_least_one_service_exists = TRUE;

        // ignore any event driven service
        if (s->SleepInterval == RUN_ON_PACKET_RECEIVE)
            continue;

        if (!min_period_initialized)
        {
            min_period = s->SleepInterval;
            min_period_initialized = TRUE;
        }
        else if (min_period > s->SleepInterval)
        {
            min_period = s->SleepInterval;
        }
    }

    // fail if there are no services
    if (!at_least_one_service_exists)
        return;

    // if there are services, but all of them are reactionary
    // just spin
    if (!min_period_initialized)
        while (TRUE);

    // otherwise, set up timer
    HANDLE timerQueueHandle = CreateTimerQueue();
    if (timerQueueHandle == INVALID_HANDLE_VALUE)
        return;

    HANDLE timerHandle = INVALID_HANDLE_VALUE;
    BOOL success = CreateTimerQueueTimer(
        &timerHandle,
        timerQueueHandle,
        &ServiceExecutorThreadCallback,
        serviceMaster,
        0,
        (DWORD) min_period,
        0
    );

    if (!success)
    {
        if (timerHandle != INVALID_HANDLE_VALUE)
            DeleteTimerQueueTimer(timerQueueHandle, timerHandle, NULL);

        DeleteTimerQueue(timerQueueHandle);
        return;
    }

    // everything is setup - spin
    while (TRUE);
}
