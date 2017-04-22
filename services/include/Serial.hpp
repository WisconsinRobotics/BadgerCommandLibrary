#pragma once

#include <string>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SerialPortHandle;
#else
    #include <unistd.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    typedef int SerialPortHandle;
#endif

#define INVALID_SERIAL_PORT_HANDLE ((SerialPortHandle) (-1))

namespace BCL
{
    class SerialPort
    {
    public:
        SerialPort();
        SerialPort(std::string port, int baud);
        ~SerialPort();
        bool Open();
        bool IsOpen() const;
        void Close();

        std::string GetPort() const;
        int GetBaud() const;

        void SetPortName(std::string& port);
        void SetBaud(int baud);

        int Write(const void *data, int size_bytes);
        int Read(void *data, int max_size_bytes);

    private:
        SerialPortHandle handle;
        bool opened;
        std::string port;
        int baud;
    };
}