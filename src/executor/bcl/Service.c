#include <string.h>
#include "bcl/Service.h"


BCL_STATUS InitializeService (
    Service *               service,
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
    service->Active = 0;
    service->SleepInterval = 0;
    strncpy(service->Name, name, SERVICE_MAX_NAME_LENGTH - 1);
    service->Execute = execute;
    service->handler = handler;

    return BCL_OK;
}