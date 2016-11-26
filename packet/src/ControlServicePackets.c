#include "ControlServicePackets.h"
#include <string.h>


BCL_STATUS InitializeActivateServicePacket (
    BclPacket *pkt 
    )
{
    return InitializeBclPacket(
        pkt,
        ACTIVATE_SERVICE_OPCODE,
        NULL,
        0,
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
        NULL,
        0,
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
        NULL,
        0,
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
        NULL,
        0,
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
        NULL,
        0,
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
        REPORT_HEARTBEAT_OPCODE,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportServiceListPacket (
    BclPacket *pkt,
    ReportServiceListPayload *payload
    )
{
    return InitializeBclPacket(
        pkt,
        REPORT_SERVICE_LIST_OPCODE,
        payload,
        MAX_SERVICE_NAME_LENGTH * payload->NumberServices,
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
        payload,
        sizeof(uint8_t),
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
    (void) payload, buffer, length, bytes_written;
    // TODO: implement 
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
    (void) payload, buffer, length, bytes_read;
    // TODO: implement
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

    if (length < 1)
        return BCL_BUFFER_TOO_SMALL;

    rpt_payload = (ReportServiceStatusPayload *)(payload);
    rpt_payload->Active = buffer[0];

    if (bytes_read)
        *bytes_read = 1;

    return BCL_OK;
}
