#include <string.h>
#include "BclStatus.h"
#include "Subsystem.h"


BCL_STATUS InitializeSubsystem (
    Subsystem *     subsystem,
    uint8_t         id
    )
{
    if (subsystem == NULL)
        return BCL_INVALID_PARAMETER;

    memset(subsystem, 0, sizeof(Subsystem));
    return BCL_OK;
}

BCL_STATUS AddService (
    Subsystem *     subsystem,
    Service *       service
    )
{
    uint8_t service_index;

    if (subsystem == NULL || service == NULL)
        return BCL_INVALID_PARAMETER;

    for (service_index= 0; service_index < MAX_SERVICES_PER_SUBSYSTEM; service_index++)
    {
        if (subsystem->_allocated_bitset >> service_index)
        {
            if (subsystem->Services[service_index]->Id == service->Id)
                return BCL_ALREADY_EXISTS;

            continue;
        }

        subsystem->_allocated_bitset |= (1 << service_index);
        subsystem->Services[service_index] = service;
        return BCL_OK;
    }

    return BCL_OUT_OF_RESOURCES;
}

BCL_STATUS RemoveService (
    Subsystem *     subsystem,
    Service *       service
    )
{
    uint8_t service_index;
    
    if (subsystem == NULL)
        return BCL_NOT_FOUND;

    for (service_index = 0; service_index < MAX_SERVICES_PER_SUBSYSTEM; service_index++)
    {
        if (((subsystem->_allocated_bitset >> service_index) & 1) == 0)
            continue;

        if (subsystem->Services[service_index] == service)
        {
            subsystem->Services[service_index] = NULL;
            subsystem->_allocated_bitset &= ~(1 << service_index);
            return BCL_OK;
        }
    }

    return BCL_NOT_FOUND;
}

BCL_STATUS RemoveServiceById (
    Subsystem *     subsystem,
    uint8_t         service_id
    )
{
    uint8_t service_index;
    
    if (subsystem == NULL)
        return BCL_NOT_FOUND;

    for (service_index = 0; service_index < MAX_SERVICES_PER_SUBSYSTEM; service_index++)
    {
        if ((subsystem->_allocated_bitset >> service_index) == 0)
            continue;

        if (subsystem->Services[service_index]->Id == service_id)
        {
            subsystem->Services[service_index] = NULL;
            subsystem->_allocated_bitset &= ~(1 << service_index);
            return BCL_OK;
        }
    }

    return BCL_NOT_FOUND;
}
