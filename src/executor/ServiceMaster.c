#include <string.h>

#include "bcl/ServiceMaster.h"

BCL_STATUS InitializeServiceMaster (
    ServiceMaster *     serviceMaster
    )
{
    if (serviceMaster == NULL)
        return BCL_INVALID_PARAMETER;

    memset(serviceMaster, 0, sizeof(ServiceMaster));
    return BCL_OK;
}

BCL_STATUS AddSubsystem (
    ServiceMaster *     serviceMaster,
    Subsystem *         subsystem
    )
{
    uint8_t i;

    if (serviceMaster == NULL || subsystem == NULL)
        return BCL_INVALID_PARAMETER;

    for (i = 0; i < MAX_SUBSYSTEMS; i++)
    {
        if (serviceMaster->_allocated_bitset >> i)
        {
            if (serviceMaster->Subsystems[i]->Id == subsystem->Id)
                return BCL_ALREADY_EXISTS;

            continue;
        }

        serviceMaster->_allocated_bitset |= (1 << i);
        serviceMaster->Subsystems[i] = subsystem;
        return BCL_OK;
    }

    return BCL_SERVICE_MASTER_FULL;
}

BCL_STATUS RemoveSubsystem (
    ServiceMaster *       serviceMaster,
    Subsystem *           subsystem
    )
{
    uint8_t i;

    if (serviceMaster == NULL || subsystem == NULL)
        return BCL_INVALID_PARAMETER;

    for (i = 0; i < MAX_SUBSYSTEMS; i++)
    {
        if (((serviceMaster->_allocated_bitset >> i) & 1) == 0)
            continue;

        if (serviceMaster[i] == subsystem)
        {
            serviceMaster->Subsystems[i] = NULL;
            serviceMaster->_allocated_bitset &= ~(1 << i);
            return BCL_OK;
        }
    }

    return BCL_NOT_FOUND;
}

BCL_STATUS RemoveSubsystemById (
    ServiceMaster *  serviceMaster,
    uint8_t          subsystem_id
)
{
    uint8_t i;

    if (serviceMaster == NULL || subsystem == NULL)
        return BCL_INVALID_PARAMETER;

    for (i = 0; i < MAX_SUBSYSTEMS; i++)
    {
        if (((serviceMaster->_allocated_bitset >> i) & 1) == 0)
            continue;

        if (serviceMaster[i]->Id == subsystem_id)
        {
            serviceMaster->Subsystems[i] = NULL;
            serviceMaster->_allocated_bitset &= ~(1 << i);
            return BCL_OK;
        }
    }

    return BCL_NOT_FOUND;
}