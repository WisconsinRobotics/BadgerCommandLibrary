#include "Serial.h"


SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
    )
{
	// TODO
	return INVALID_SERIAL_HANDLE;
}

BCL_STATUS SerialPortWriteData (
    SerialHandle handle,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
    )
{
    return BCL_OK;
}

BCL_STATUS SerialPortReadData (
    SerialHandle handle,
    void *buffer,
    uint8_t size,
    uint8_t *bytes_read
    )
{
	return BCL_OK;
}

void CloseSerialPort (
    SerialHandle handle
    )
{

}