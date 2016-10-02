#include "SerialPort.hpp"
#include <msclr\marshal_cppstd.h>

using namespace BclSharp;


SerialPort::SerialPort(System::String^ port, System::Int32 baud_rate)
{
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(port);

    this->serialPort = new BCL::SerialPort(standardString.c_str(), baud_rate);
}

SerialPort::~SerialPort()
{
    if (this->serialPort)
        delete this->serialPort;
}

System::Boolean SerialPort::Open()
{
    return this->serialPort->Open();
}

System::Boolean SerialPort::IsOpen()
{
    return this->serialPort->IsOpen();
}

void SerialPort::Close()
{
    this->serialPort->Close();
}

void SerialPort::Write(array<System::Byte>^ buffer, System::Int32 length)
{
    pin_ptr<System::Byte> converted = &buffer[0];
    this->serialPort->Write(converted, length);
}

System::Int32 SerialPort::Read(array<System::Byte>^ buffer, System::Int32 length)
{
    pin_ptr<System::Byte> converted = &buffer[0];
    return this->serialPort->Read(converted, length);
}
