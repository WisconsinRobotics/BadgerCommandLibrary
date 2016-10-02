#pragma once

#include "Packet.h"

namespace BclSharp
{
    public ref struct Address
    {
        System::Byte RobotID;
        System::Byte ServiceID;
    };

    public ref class Packet abstract
    {
    public:
        Packet();
        virtual ~Packet();

        virtual array<System::Byte>^ Serialize();
        virtual System::Boolean Deserialize(array<System::Byte>^ buffer, System::Int32 length);

        property System::Int32 Opcode
        {
            System::Int32 get()
            {
                return this->base_pkt->Header.Opcode;
            }
        }

        property Address^ Source
        {
            Address^ get()
            {
                auto raw_address = this->base_pkt->Header.Source;
                Address^ a = gcnew Address();
                a->RobotID = raw_address.RobotID;
                a->ServiceID = raw_address.ServiceID;

                return a;
            }

            void set(Address^ addr)
            {
                if (addr == nullptr)
                    return;

                auto src = this->base_pkt->Header.Source;
                src.RobotID = addr->RobotID;
                src.ServiceID = addr->ServiceID;
            }
        }

        property Address^ Destination
        {
            Address^ get()
            {
                auto raw_address = this->base_pkt->Header.Destination;
                Address^ a = gcnew Address();
                a->RobotID = raw_address.RobotID;
                a->ServiceID = raw_address.ServiceID;

                return a;
            }

            void set(Address^ addr)
            {
                if (addr == nullptr)
                    return;

                auto src = this->base_pkt->Header.Destination;
                src.RobotID = addr->RobotID;
                src.ServiceID = addr->ServiceID;
            }
        }

        property System::Int32 PayloadSize
        {
            System::Int32 get()
            {
                return this->base_pkt->Header.PayloadSize;
            }
        }

    protected:
        BclPacket *base_pkt;
    };
}
