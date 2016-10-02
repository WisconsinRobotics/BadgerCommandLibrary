#pragma once

#include "Serial.hpp"

namespace BclSharp
{
    public ref class SerialPort
    {
    public:
        // assumed no parity, 1 stop bit, and 8 bits per byte
        SerialPort(System::String^ port, System::Int32 baud_rate);
        ~SerialPort();
        System::Boolean Open();
        System::Boolean IsOpen();
        void Close();
        void Write(array<System::Byte>^ buffer, System::Int32 length);
        System::Int32 Read(array<System::Byte>^ buffer, System::Int32 length);

    private:
        BCL::SerialPort *serialPort;
    };
}
