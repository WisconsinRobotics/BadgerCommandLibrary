#include "ControlServicePackets.h"
#include "ServiceMaster.h"
#include <string.h>


BCL_STATUS InitializeActivateServicePacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        ACTIVATE_SERVICE_OPCODE,
        PACKET_MIN_SIZE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeDeactivateServicePacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        DEACTIVATE_SERVICE_OPCODE,
        PACKET_MIN_SIZE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeQueryServiceListPacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        QUERY_SERVICE_LIST_OPCODE,
        PACKET_MIN_SIZE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeQueryServiceStatusPacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        QUERY_SERVICE_STATUS_OPCODE,
        PACKET_MIN_SIZE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeQueryHeartbeatPacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        QUERY_HEARTBEAT_OPCODE,
        PACKET_MIN_SIZE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportHeartbeatPacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        ACTIVATE_SERVICE_OPCODE,
        REPORT_HEARTBEAT_OPCODE,
        NULL,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportServiceListPacket (
    BclPacket *pkt,
    ReportServiceListPayload *payload,
    uint8_t number_services
    )
{
    if (number_services > (MAX_SERVICES_PER_SUBSYSTEM * MAX_SUBSYSTEMS))
        return BCL_INVALID_PARAMETER;

    return InitializeBclPacket(
        pkt,
        REPORT_SERVICE_LIST_OPCODE,
        PACKET_MIN_SIZE + SERVICE_MAX_NAME_LENGTH * number_services,
        payload,
        &SerializeReportServiceListPayload,
        &DeserializeReportServiceListPayload
    );
}

BCL_STATUS InitializeReportServiceStatusPacket (
    BclPacket *pkt,
    ReportServiceStatusPayload *payload
    )
{
    return InitializeBclPacket(
        pkt,
        REPORT_SERVICE_STATUS_OPCODE,
        PACKET_MIN_SIZE + sizeof(uint8_t),
        payload,
        &SerializeReportServiceStatusPayload,
        &DeserializeReportServiceStatusPayload
    );
}

BCL_STATUS SerializeReportServiceListPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
    )
{
    const ReportServiceListPayload *rpt_payload;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    rpt_payload = (const ReportServiceListPayload *)(payload);

    // TODO:
    // copy strings into buffer

    // length checks

    // update  bytes_written, if not null

    return BCL_OK;
}

BCL_STATUS SerializeReportServiceStatusPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
    )
{
    const ReportServiceStatusPayload *rpt_payload;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    // length too small?
    if (length < sizeof(uint8_t))
        return BCL_BUFFER_TOO_SMALL;

    rpt_payload = (const ReportServiceStatusPayload *)(payload);
    buffer[0] = rpt_payload->Active;
    
    if (bytes_written)
        *bytes_written = sizeof(uint8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeReportServiceListPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
    )
{
    ReportServiceListPayload *rpt_payload;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    rpt_payload = (ReportServiceListPayload *)(payload);
    if (!payload->ServiceNameList)
        return BCL_INVALID_PARAMETER;
    
    // TODO: parse null terminated ascii strings
    // updated bytes_read, if not null

    return BCL_OK;
}

BCL_STATUS DeserializeReportServiceStatusPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
    )
{
    ReportServiceStatusPayload *rpt_payload;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    rpt_payload = (ReportServiceStatusPayload *)(payload);
    payload->Status = buffer[0];

    if (bytes_read)
        *bytes_read = 1;

    return BCL_OK;
}
