#pragma once

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SerialPortHandle;
#else
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <string.h>
    typedef int SerialPortHandle;
#endif

#define INVALID_SERIAL_PORT_HANDLE ((SerialPortHandle) (-1))

namespace BCL
{
    class SerialPort
    {
    public:
        SerialPort();
        SerialPort(const char *port, int baud);
        ~SerialPort();
        bool Open();
        bool IsOpen() const;
        void Close();

        const char * GetPort() const;
        int GetBaud() const;

        void SetPortName(const char *port);
        void SetBaud(int baud);

        int Write(const void *data, int size_bytes);
        int Read(void *data, int max_size_bytes);
    private:
        SerialPortHandle handle;
        bool opened;
        const char *port;
        int baud;
    };
}