#ifndef _SERIAL_H
#define _SERIAL_H

#include "BclConfig.h"
#include "BclStatus.h"
#include <stdint.h>

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SerialHandle;
#else
    typedef int SerialHandle;
#endif

#define INVALID_SERIAL_HANDLE ((SerialHandle)(-1))

/**
 * @brief Opens the specified serial port.
 *
 * On some platforms (i.e. microcontrollers), there is no string for serial ports.
 * You may pass in NULL as the port name.
 *
 * @param port      A string to the serial port (COM* on Windows, /dev/ttyS* on linux)
 * @param baudrate  The serial port baudrate.
 * @return A handle to the serial port, or INVALID_SERIAL_HANDLE on failure.
 */
SerialHandle OpenSerialPort (
    const char *port, 
    int baudrate
);

/**
 * Writes the specified data into the serial port.
 *
 * @param handle            A handle to the serial port.
 * @param buffer            The data to be written.
 * @param length            The length of the buffer.
 * @param bytes_written     An optional pointer to store how many bytes were actually written.
 * @return BCL_OK on success. 
 */
BCL_STATUS SerialPortWriteData(
    SerialHandle handle,
    const void *buffer,
    uint8_t length,
    uint8_t *bytes_written
);

/**
 * @brief Writes the specified data into the serial port.
 *
 * @param handle            A handle to the serial port.
 * @param buffer            The data to be written.
 * @param length            The length of the buffer.
 * @param bytes_read        An optional pointer to store how many bytes were actually read.
 * @return BCL_OK on success. 
 */
BCL_STATUS SerialPortReadData (
    SerialHandle    handle,
    void *          buffer,
    uint8_t         length,
    uint8_t *       bytes_read
);

/**
 * @brief Closes the serial port.
 *
 * @param handle    The handle to an open serial port.
 * @return void
 */
void CloseSerialPort (
    SerialHandle handle
);

#endif