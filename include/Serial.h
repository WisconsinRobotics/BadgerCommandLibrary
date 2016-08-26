#ifdef _SERIAL_H
#define _SERIAL_H

#include "BclConfig.h"
#include "BclStatus.h"
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define SerialHandle HANDLE
#else
    #define SerialHandle int
#endif

#define INVALID_SERIAL_HANDLE ((SerialHandle)(-1))

struct
{
    SerialHandle handles[MAX_SERIAL];
    uint8_t _allocated_bitset;
} serial_handles;


void InitializeSerialTracker(void)
{
    memset(&serial_handles.handles, INVALID_SERIAL_HANDLE, sizeof(SerialHandle) * MAX_SERIAL);
    serial_handles._allocated_bitset = 0;
}

SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
);

BCL_STATUS SerialPortWriteData (
    SerialHandle handle,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
);

BCL_STATUS SerialPortReadData (
    SerialHandle handle,
    void *buffer,
    uint8_t size,
    uint8_t *bytes_read
);

void CloseSerialPort (
    SerialHandle handle
);
