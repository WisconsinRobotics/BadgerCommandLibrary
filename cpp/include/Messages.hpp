#pragma once

namespace BCL
{
    class ActivateService
    {
        const uint8_t opcode = 0xAC;
        public:
            ActivateService(int subsystemID, int serviceID);
            ~ActivateService(void);
            int GetSubsystemID(void);
            int GetServiceID(void);
            void SetSubsystemID(int subsystemID);
            void SetServiceID(int serviceID);
        protected:
            int subsystemID;
            int serviceID;
    }

    class DeactivateService
    {
        const uint8_t opcode = 0xDC;
        public:
            DeactivateService(int subsystemID, int serviceID);
            ~DeactivateService(void);
            int GetSubsystemID(void);
            int GetServiceID(void);
            void SetSubsystemID(int subsystemID);
            void SetServiceID(int serviceID);
        protected:
            int subsystemID;
            int serviceID;
    }

    class QueryServiceList
    {
        const uint8_t opcode = 0x70;
        public:
            QueryServiceList(void);
            ~QueryServiceList(void);
    }

    class QueryServiceStatus
    {
        const uint8_t opcode = 0x73;
        public:
            QueryServiceStatus(void);
            ~QueryServiceStatus(void);
    }

    class QueryHeartbeat
    {
        const uint8_t opcode = 0x90;
        public:
            QueryHeartbeat(void);
            ~QueryHeartbeat(void);
    }

    class ReportServiceList
    {
        const uint8_t opcode = 0x71;
        public:
            ReportServiceList(void);
            ~ReportServiceList(void);
    }

    class ReportHeartbeat
    {
        const uint8_t opcode = 0x91;
        public:
            ReportHeartbeat(void);
            ~ReportHeartbeat(void);
    }

    class ReportServiceStatus
    {
        const uint8_t opcode = 0x74;
        public:
            ReportServiceStatus(void);
            ~ReportServiceStatus(void);
    }

}
