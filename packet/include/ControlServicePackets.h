#ifndef _CONTROL_SERVICE_PACKETS_H
#define _CONTROL_SERVICE_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

/* Reserved Packets are 0xF0 and above */
#define ACTIVATE_SERVICE_OPCODE         0xF0
#define DEACTIVATE_SERVICE_OPCODE       0xF1
#define QUERY_SERVICE_LIST_OPCODE       0xF2
#define QUERY_SERVICE_STATUS_OPCODE     0xF3
#define QUERY_HEARTBEAT_OPCODE          0xF4
#define REPORT_SERVICE_LIST_OPCODE      0xF5
#define REPORT_SERVICE_STATUS_OPCODE    0xF6
#define REPORT_HEARTBEAT_OPCODE         0xF7

#define MAX_SERVICE_NAME_LENGTH         10

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char **ServiceNameList;
    uint8_t NumberServices;
} ReportServiceListPayload;

typedef struct
{
    uint8_t Active;
} ReportServiceStatusPayload;

/* Initialization functions */

BCL_STATUS InitializeActivateServicePacket (
    BclPacket *pkt
);

BCL_STATUS InitializeDeactivateServicePacket (
    BclPacket *pkt 
);

BCL_STATUS InitializeQueryServiceListPacket (
    BclPacket *pkt 
);

BCL_STATUS InitializeQueryServiceStatusPacket (
    BclPacket *pkt 
);

BCL_STATUS InitializeQueryHeartbeatPacket (
    BclPacket *pkt 
);

BCL_STATUS InitializeReportHeartbeatPacket (
    BclPacket *pkt 
);

BCL_STATUS InitializeReportServiceListPacket (
    BclPacket *pkt,
    ReportServiceListPayload *payload
);

BCL_STATUS InitializeReportServiceStatusPacket (
    BclPacket *pkt,
    ReportServiceStatusPayload *payload
);

/* Serialization functions */

BCL_STATUS SerializeReportServiceListPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeReportServiceStatusPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

/* Deserialization functions */

BCL_STATUS DeserializeReportServiceListPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
);

BCL_STATUS DeserializeReportServiceStatusPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
);

#ifdef __cplusplus
}
#endif

#endif
