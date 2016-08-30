#include <string.h>
#include "Service.h"


BCL_STATUS InitializeService(
    Service *               service,
    ServiceData             data,
    uint8_t                 id,
    const char *            name,
    ServiceExecutor         execute,
    ServicePacketHandler    handler
    )
{
    if (service == NULL || name == NULL)
        return BCL_INVALID_PARAMETER;

    memset(service, 0, sizeof(Service));

    service->Id = id;
    service->Data = data;
    service->Active = 0;
    service->SleepInterval = 0;
    strncpy(service->Name, name, MAX_SERVICE_NAME_LENGTH - 1);
    service->Execute = &execute;
    service->HandlePacket = &handler;
    service->LastPacketOrigin.Interface = LPI_NONE;

    return BCL_OK;
}