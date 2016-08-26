#include "Serial.h"


SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
    )
{

}

BCL_STATUS SerialPortWriteData (
    SerialHandle handle,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
    )
{
    
}

BCL_STATUS SerialPortReadData (
    SerialHandle handle,
    void *buffer,
    uint8_t size,
    uint8_t *bytes_read
    )
{

}

void CloseSerialPort (
    SerialHandle handle
    )
{

}