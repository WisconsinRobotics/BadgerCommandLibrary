#include "Serial.h"
#include <stdint.h>

SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
    )
{
    DCB dcb;
    COMMTIMEOUTS commTO;
    SerialHandle handle;
    
    if (!port)
        return INVALID_SERIAL_HANDLE;
    
    handle = CreateFileA(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_FLAG_WRITE_THROUGH,
        0
    );
        
    if (handle == INVALID_HANDLE_VALUE)
        return INVALID_SERIAL_HANDLE;
    
    memset(&dcb, 0, sizeof(DCB));
    if (!GetCommState(handle, &dcb))
    {
        CloseHandle(handle);
        return INVALID_SERIAL_HANDLE;
    }

    dcb.BaudRate = baudrate;
    dcb.fParity = FALSE;
    dcb.StopBits = ONESTOPBIT;
    dcb.ByteSize = 8;
    dcb.DCBlength = sizeof(dcb);
    if (!SetCommState(handle, &dcb))
    {
        CloseHandle(handle);
        return INVALID_SERIAL_HANDLE;
    }
    
    ZeroMemory(&commTO, sizeof(COMMTIMEOUTS));
    commTO.ReadIntervalTimeout = MAXDWORD;
    if (!SetCommTimeouts(handle, &commTO))
    {
        CloseHandle(handle);
        return INVALID_SERIAL_HANDLE;
    }
    
    return handle;
}

BCL_STATUS SerialPortWriteData (
    SerialHandle handle,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
    )
{
    DWORD written;
    
    if (!buffer)
        return BCL_INVALID_PARAMETER;

    if (!WriteFile(handle, buffer, length, &written, NULL))
        return BCL_SERIAL_ERROR;
    
    if (bytes_written)
        *bytes_written = (uint8_t) written;

    return BCL_OK;
}

BCL_STATUS SerialPortReadData (
    SerialHandle handle,
    void *buffer,
    uint8_t length,
    uint8_t *bytes_read
    )
{
    DWORD read;
    
    if (!buffer)
        return BCL_INVALID_PARAMETER;

    if (!ReadFile(handle, buffer, length, &read, NULL))
        return BCL_SERIAL_ERROR;
    
    if (bytes_read)
        *bytes_read = (uint8_t) read;

    return BCL_OK;
}

void CloseSerialPort (
    SerialHandle handle
    )
{
    CloseHandle(handle);
}