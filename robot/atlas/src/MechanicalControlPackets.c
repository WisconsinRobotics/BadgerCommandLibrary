#if ROBOT == Atlas
#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

// Initialization
BCL_STATUS InitializeSetTankDriveSpeedPacket(
        BclPacket *pkt,
        TankDrivePayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_TANK_DRIVE_SPEED,
            payload,
            2 * sizeof(int8_t),
            &SerializeTankDriveSpeedPayload,
            &DeserializeTankDriveSpeedPayload
    );
}

BCL_STATUS InitializeSetAllWheelSpeedPacket(
        BclPacket *pkt,
        AllWheelSpeedPayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_ALL_WHEEL_SPEED,
            payload,
            sizeof(int8_t) + 4 * sizeof(int8_t),
            &SerializeAllWheelSpeedPayload,
            &DeserializeAllWheelSpeedPayload
    );
}

//Serialize
BCL_STATUS SerializeTankDriveSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const TankDrivePayload *tdp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    // enough size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    tdp = (const TankDrivePayload *)(payload);
    buffer[0] = tdp->left;
    buffer[1] = tdp->right;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeAllWheelSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const AllWheelSpeedPayload *awsp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < (sizeof(uint8_t) + NUMBER_OF_WHEELS * sizeof(int8_t)))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (const AllWheelSpeedPayload *)payload;
    buffer[FRONT_LEFT_WHEEL] = awsp->front_left;
    buffer[BACK_LEFT_WHEEL] = awsp->back_left;
    buffer[FRONT_RIGHT_WHEEL] = awsp->front_right;
    buffer[BACK_RIGHT_WHEEL] = awsp->back_right;

    if (bytes_written)
        *bytes_written = sizeof(uint8_t) + NUMBER_OF_WHEELS * sizeof(int8_t);

    return BCL_OK;
}

//Deserialize
BCL_STATUS DeserializeTankDriveSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    TankDrivePayload *tdp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    tdp = (TankDrivePayload *)payload;
    tdp->left = buffer[0];
    tdp->right = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeAllWheelSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    AllWheelSpeedPayload *awsp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint8_t) + NUMBER_OF_WHEELS * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (AllWheelSpeedPayload *)payload;
    awsp->front_left = buffer[FRONT_LEFT_WHEEL];
    awsp->back_left = buffer[BACK_LEFT_WHEEL];
    awsp->front_right = buffer[FRONT_RIGHT_WHEEL];
    awsp->back_right = buffer[BACK_RIGHT_WHEEL];

    if (bytes_read)
        *bytes_read = sizeof(uint8_t) + NUMBER_OF_WHEELS * sizeof(int8_t);

    return BCL_OK;
}
#endif