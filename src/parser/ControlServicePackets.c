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
    )
{
    if (number_services > (MAX_SERVICES_PER_SUBSYSTEM * MAX_SUBSYSTEMS))
        return BCL_INVALID_PARAMETER;

    return InitializeBclPacket(
        pkt,
        REPORT_SERVICE_LIST_OPCODE,
        PACKET_MIN_SIZE + MAX_SERVICE_NAME_LENGTH * payload->NumberServices,
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
    uint8_t payload_length;
    uint8_t i;
    uint8_t buf_offset;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    rpt_payload = (const ReportServiceListPayload *)(payload);

    for (i = 0; i < rpt_payload->NumberServices; i++)
        payload_length += strlen(payload->ServiceNameList[i]);

    if (payload_length > length)
        return BCL_BUFFER_TOO_SMALL;

    // copy strings into buffer
    // XXX: verify
    for (i = 0, buf_offset = 0; i < rpt_payload->NumberServices; i++)
    {
        strncpy(buffer + buf_offset, payload->ServiceNameList[i], MAX_SERVICE_NAME_LENGTH);
    }

    if (bytes_written)
        *bytes_written = payload_length;

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
    uint8_t i;
    uint8_t buf_offset;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    rpt_payload = (ReportServiceListPayload *)(payload);
    if (!payload->ServiceNameList)
        return BCL_INVALID_PARAMETER;
    
    // parse strings
    // XXX: verify
    for (i = 0, buf_offset = 0; i < rpt_payload->NumberServices; i++)
    {
        strncpy(rpt_payload->ServiceNameList[i], buffer + buf_offset, MAX_SERVICE_NAME_LENGTH);
    }

    if (bytes_read)
        *bytes_read = buf_offset;

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
