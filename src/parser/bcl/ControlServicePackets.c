#include "ControlServicePackets.h"


// should the function signature include Subsystem?
void InitializeReportServiceListPacket(ReportServiceList *pkt)
{
    if (!pkt)
        return;

    // since freshly initialized, no services in service list
    // hence, PACKET_MIN_SIZE for size
    InitializeBclPacket(pkt, REPORT_SERVICE_LIST_OPCODE, PACKET_MIN_SIZE);
    pkt->ServiceNameList = NULL;
}

void InitializeReportServiceStatusPacket(ReportServiceStatus *pkt)
{
    if (!pkt)
        return;

    InitializeBclPacket(pkt, REPORT_SERVICE_STATUS_OPCODE, PACKET_MIN_SIZE + sizeof(uint8_t));
    pkt->Active = 0;
}

uint8_t SerializeReportServiceListPacket(ReportServiceList *pkt, uint8_t *payload, int payloadLength)
{
    return -1;
}

uint8_t SerializeReportServiceStatusPacket(ReportServiceStatus *pkt, uint8_t *payload, int payloadLength)
{
    return -1;
}

uint8_t DeserializeReportServiceListPacket(ReportServiceList *pkt, uint8_t *payload, int payloadLength)
{
    return -1;
}

uint8_t DeserializeReportServiceStatusPacket(ReportServiceStatus *pkt, uint8_t *payload, int payloadLength)
{
    return -1;
}