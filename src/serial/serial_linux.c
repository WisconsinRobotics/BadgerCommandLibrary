#include "Serial.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>


SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
    )
{
    struct termios serialPortProperties;
    int handle;

    if (!port || baudrate < 0)
        return INVALID_SERIAL_HANDLE;

    handle = open(port, O_RDWR | O_NOCTTY);
    if (handle < 0)
        return INVALID_SERIAL_HANDLE;
        
    memset(&serialPortProperties, 0, sizeof(struct termios));
    tcgetattr(handle, &serialPortProperties);
    cfsetospeed(&serialPortProperties, baudrate);
    cfsetispeed(&serialPortProperties, baudrate);

    serialPortProperties.c_cflag = (serialPortProperties.c_cflag & ~CSIZE) | CS8;
    serialPortProperties.c_cflag &= ~(PARENB | PARODD);
    serialPortProperties.c_cflag &= ~CSTOPB;
    tcflush(handle, TCIFLUSH);
    tcsetattr(handle, TCSANOW, &serialPortProperties);

    return handle;
}

BCL_STATUS SerialPortWriteData (
    SerialHandle handle,
    const void *buffer,
    uint8_t size,
    uint8_t *bytes_written
    )
{
    int written;

    if (handle < 0)
        return BCL_INVALID_PARAMETER;
        
     written = write(handle, buffer, size);
     if (written < 0)
        return BCL_SERIAL_ERROR;

    if (bytes_written)
        *bytes_written = written;

    return BCL_OK;
}

BCL_STATUS SerialPortReadData (
    SerialHandle handle,
    void *buffer,
    uint8_t size,
    uint8_t *bytes_read
    )
{
    int num_read;

    if (handle < 0 || !buffer)
        return BCL_INVALID_PARAMETER;
        
    num_read = read(handle, buffer, size);
    if (num_read < 0)
        return BCL_SERIAL_ERROR;

    if (bytes_read)
        *bytes_read = num_read;

    return BCL_OK;
}

void CloseSerialPort (
    SerialHandle handle
    )
{
    close(handle);
}