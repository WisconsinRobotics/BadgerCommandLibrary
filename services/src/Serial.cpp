#include "Serial.hpp"
#include <stdexcept>

using namespace BCL;


SerialPort::SerialPort()
{
    this->port = nullptr;
    this->baud = 0;
    this->opened = false;
    this->recovering = false;
    this->handle = INVALID_SERIAL_PORT_HANDLE;
}

SerialPort::SerialPort(std::string port, int baud)
{
    this->port = port;
    this->baud = baud;
    this->opened = false;
    this->recovering = false;
	this->handle = INVALID_SERIAL_PORT_HANDLE;
}

SerialPort::~SerialPort()
{
    this->Close();
}

bool SerialPort::IsOpen() const
{
    return this->opened;
}

std::string SerialPort::GetPort() const
{
    return this->port;
}

bool SerialPort::IsRecovering() const
{
    return this->recovering;
}

int SerialPort::GetBaud() const
{
    return this->baud;
}

void SerialPort::SetPortName(std::string& portname)
{
    this->port = portname;
}

void SerialPort::SetBaud(int baudrate)
{
    this->baud = baudrate;
}

#ifdef _WIN32
bool SerialPort::Open()
{
    DCB dcb;
    COMMTIMEOUTS commTO;
    
    if (this->opened && !this->recovering)
        return true;
    
    handle = CreateFileA(
        port.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,
        0
    );
        
    if (handle == INVALID_HANDLE_VALUE)
        return false;
    
    // configure serial port settings
    memset(&dcb, 0, sizeof(DCB));
    if (!GetCommState(handle, &dcb))
    {
        CloseHandle(handle);
        return false;
    }

    dcb.BaudRate = baud;
    dcb.fParity = FALSE;
    dcb.StopBits = ONESTOPBIT;
    dcb.ByteSize = 8;
    dcb.DCBlength = sizeof(dcb);
    if (!SetCommState(handle, &dcb))
    {
        CloseHandle(handle);
        return false;
    }
    
    memset(&commTO, 0, sizeof(COMMTIMEOUTS));
    commTO.ReadIntervalTimeout = MAXDWORD;
    if (!SetCommTimeouts(handle, &commTO))
    {
        CloseHandle(handle);
        return false;
    }

    // configure events to detect loss 
    if (!SetCommMask(handle, EV_RXCHAR | EV_TXEMPTY))
    {
        CloseHandle(handle);
        return false;
    }

    this->opened = true;
    return true;
}

void SerialPort::Close()
{
	if (this->opened)
        CloseHandle(handle);

    this->opened = false;
}

int SerialPort::Write(const void *data, int size_bytes)
{
    DWORD bytesWritten;
    
    if (!this->opened && !this->recovering)
        return -1;
    
    if (!WriteFile(handle, data, size_bytes, &bytesWritten, nullptr))
    {
        this->recovering = true;
        if (!this->AttemptRecovery())
            return -1;

        // recovery successful, retry //
        if (!WriteFile(handle, data, size_bytes, &bytesWritten, nullptr))
            return -1;
    }

    return bytesWritten;
}

bool SerialPort::AttemptRecovery()
{
    if (!this->recovering)
        return true;

    DWORD error = GetLastError();
    switch (error)
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_GEN_FAILURE:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_BAD_COMMAND:
            // attempt to reopen //
            if (!this->Open())
                return false;

            // reopen successful //
            this->recovering = false;
            return true;
        default:
            return false;
    }
}

int SerialPort::Read(void *data, int max_size_bytes)
{
    DWORD bytesRead;
    
    if (!this->opened && !this->recovering)
        return -1;
    
    DWORD dwReceived = 0;
    if (!WaitCommEvent(this->handle, &dwReceived, NULL))
    {
        this->recovering = true;
        if (!this->AttemptRecovery())
            return -1;
    }

    if (!ReadFile(handle, data, max_size_bytes, &bytesRead, nullptr))
        return -1;

    return bytesRead;
}

#else
bool SerialPort::Open()
{
    struct termios serialPortProperties;

    if (this->opened && !this->recovering)
        return true;

    handle = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (handle < 0)
        return false;
        
    memset(&serialPortProperties, 0, sizeof(struct termios));
    tcgetattr(handle, &serialPortProperties);
    cfsetospeed(&serialPortProperties, baud);
    cfsetispeed(&serialPortProperties, baud);

    serialPortProperties.c_cflag = (serialPortProperties.c_cflag & ~CSIZE) | CS8;
    serialPortProperties.c_cflag &= ~(PARENB | PARODD);
    serialPortProperties.c_cflag &= ~CSTOPB;
    tcflush(handle, TCIFLUSH);
    tcsetattr(handle, TCSANOW, &serialPortProperties);

    udev = udev_new();
    if (!udev)
    {
        close(handle);
        return false;
    }

    mon = udev_monitor_new_from_netlink(udev, "udev");
    if (!mon)
    {
        close(handle);
        udev_unref(udev);
        return false;
    }

	udev_monitor_filter_add_match_subsystem_devtype(mon, "tty", NULL);
	udev_monitor_enable_receiving(mon);
	mon_fd = udev_monitor_get_fd(mon);

    this->opened = true;  
    return true;
}

void SerialPort::Close()
{
    if (this->opened)
        close(handle);

    if (mon)
        udev_monitor_unref(mon);

    if (udev)
        udev_unref(udev);

    this->opened = false;
}

bool SerialPort::AttemptRecovery()
{
    return true; // do nothing //
}

int SerialPort::Write(const void *data, int size_bytes)
{
    if (!this->opened && !this->recovering)
        return -1;

    // check device status
    int ret = 0;
    do
    {
        struct timeval tv = { 0, 0 };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(mon_fd, &fds);
        ret = select(mon_fd + 1, &fds, nullptr, nullptr, &tv);
        if (ret > 0)
        {
            struct udev_device *dev = udev_monitor_receive_device(mon);
            const char *dev_action = udev_device_get_action(dev);
            if (strcmp("remove", dev_action) == 0)
            {
                close(this->handle);
                this->recovering = true;
                return -1;
            }
            else if (strcmp("add", dev_action) == 0)
            {
                const char *devnode = udev_device_get_devnode(dev);
                if (strcmp(port.c_str(), devnode) != 0)
                    return -1;
                assert(this->Open());
                this->recovering = false;
            }
        }
        else if (this->recovering)
        {
            // still recovering //
            return -1;
        }

    } while (ret > 0);

    // normal write //
    return write(handle, data, size_bytes);
}

int SerialPort::Read(void *data, int max_size_bytes)
{
    if (!this->opened && !this->recovering)
        return -1;
        
    // check device status
    int ret = 0;
    do
    {
        struct timeval tv = { 0, 0 };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(mon_fd, &fds);
        ret = select(mon_fd + 1, &fds, nullptr, nullptr, &tv);
        if (ret > 0)
        {
            struct udev_device *dev = udev_monitor_receive_device(mon);
            const char *dev_action = udev_device_get_action(dev);
            if (strcmp("remove", dev_action) == 0)
            {
                close(this->handle);
                this->recovering = true;
                return -1;
            }
            else if (strcmp("add", dev_action) == 0)
            {
                const char *devnode = udev_device_get_devnode(dev);
                if (strcmp(port.c_str(), devnode) != 0)
                    return -1;

                assert(this->Open());
                this->recovering = false;
            }
        }
        else if (this->recovering)
        {
            // still recovering //
            return -1;
        }

    } while (ret > 0);

    return read(handle, data, max_size_bytes);
}

#endif
