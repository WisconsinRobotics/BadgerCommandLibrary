#ifndef _CONTROL_SERVICE_PACKETS_H
#define _CONTROL_SERVICE_PACKETS_H

#define ACTIVATE_SERVICE_OPCODE         0xAC
#define DEACTIVATE_SERVICE_OPCODE       0xDC
#define QUERY_SERVICE_LIST_OPCODE       0x70
#define QUERY_SERVICE_STATUS_OPCODE     0x73
#define QUERY_HEARTBEAT_OPCODE          0x90
#define REPORT_SERVICE_LIST_OPCODE      0x71
#define REPORT_SERVICE_STATUS_OPCODE    0x74
#define REPORT_HEARTBEAT_OPCODE         0x91

typedef struct ActivateService      BclPacket;
typedef struct DeactivateService    BclPacket;
typedef struct QueryServiceList	    BclPacket;
typedef struct QueryServiceStatus   BclPacket;
typedef struct QueryHeartbeat       BclPacket;
typedef struct ReportServiceList    ReportServiceList;
typedef struct ReportServiceStatus  ReportServiceStatus;
typedef struct ReportHeartbeat      BclPacket;

struct ReportServiceList
{
    BclPacket;
    char** ServiceNameList;
};

struct ReportServiceStatus
{
    BclPacket;
    uint8_t Active;
};

/* Initialization functions */
#define InitializeActivateServicePacket(pkt)    InitializeBclPacket(pkt, ACTIVATE_SERVICE_OPCODE, PACKET_MIN_SIZE)
#define InitializeDeactivateServicePacket(pkt)  InitializeBclPacket(pkt, DEACTIVATE_SERVICE_OPCODE, PACKET_MIN_SIZE)
#define InitializeQueryServiceListPacket(pkt)   InitializeBclPacket(pkt, QUERY_SERVICE_LIST_OPCODE, PACKET_MIN_SIZE)
#define InitializeQueryServiceStatusPacket(pkt) InitializeBclPacket(pkt, QUERY_SERVICE_STATUS_OPCODE, PACKET_MIN_SIZE)
#define InitializeQueryHeartbeatPacket(pkt)     InitializeBclPacket(pkt, QUERY_HEARTBEAT_OPCODE, PACKET_MIN_SIZE)
#define InitializeReportHeartbeatPacket(pkt)    InitializeBclPacket(pkt, REPORT_HEARTBEAT_OPCODE, PACKET_MIN_SIZE)

void InitializeReportServiceListPacket(ReportServiceList *pkt);
void InitializeReportServiceStatusPacket(ReportServiceStatus *pkt);

/* Serialization functions */
#define SerializeActivateServicePacket      SerializeBclPacket
#define SerializeDeactivateServicePacket    SerializeBclPacket
#define SerializeQueryServiceListPacket     SerializeBclPacket
#define SerializeQueryServiceStatusPacket   SerializeBclPacket
#define SerializeQueryHeartbeatPacket       SerializeBclPacket
#define SerializeReportHeartbeatPacket      SerializeBclPacket

uint8_t SerializeReportServiceListPacket(ReportServiceList *pkt, uint8_t *payload, int payloadLength);
uint8_t SerializeReportServiceStatusPacket(ReportServiceStatus *pkt, uint8_t *payload, int payloadLength);

/* Deserialization functions */
#define DeserializeActivateServicePacket    DeserializeBclPacket
#define DeserializeDeactivateServicePacket  DeserializeBclPacket
#define DeserializeQueryServiceListPacket   DeserializeBclPacket
#define DeserializeQueryServiceStatusPacket DeserializeBclPacket
#define DeserializeQueryHeartbeatPacket     DeserializeBclPacket
#define DeserializeReportHeartbeatPacket    DeserializeBclPacket

uint8_t DeserializeReportServiceListPacket(ReportServiceList *pkt, uint8_t *payload, int payloadLength);
uint8_t DeserializeReportServiceStatusPacket(ReportServiceStatus *pkt, uint8_t *payload, int payloadLength);

#endif