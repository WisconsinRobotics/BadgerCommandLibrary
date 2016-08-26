#ifndef _SERIAL_H
#define _SERIAL_H

#include "BclConfig.h"
#include "BclStatus.h"
#include <stdint.h>

#ifdef _WIN32
    #include <windows.h>
    #define SerialHandle HANDLE
#else
    #define SerialHandle int
#endif

#define INVALID_SERIAL_HANDLE ((SerialHandle)(-1))

SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
);

BCL_STATUS SerialPortWriteData(
    SerialHandle handle,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
);

BCL_STATUS SerialPortReadData (
    SerialHandle    handle,
    void *          buffer,
    uint8_t         length,
    uint8_t *       bytes_read
);

void CloseSerialPort (
    SerialHandle handle
);

#endif