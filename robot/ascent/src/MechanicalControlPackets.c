#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

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
            sizeof(uint8_t) + 6 * sizeof(int8_t),
            &SerializeAllWheelSpeedPayload,
            &DeserializeAllWheelSpeedPayload
    );
}

BCL_STATUS InitializeQueryArmPositionPacket(
        BclPacket *pkt
)
{
    return InitializeBclPacket(
            pkt,
            QUERY_ARM_POS,
            NULL,
            0,
            NULL,
            NULL
    );
}

BCL_STATUS InitializeReportArmPositionPacket(
        BclPacket               *pkt,
        ArmPositionPayload      *payload
)
{
    return InitializeBclPacket(
            pkt,
            REPORT_ARM_POS,
            payload,
            sizeof(uint8_t) + 6 * sizeof(int8_t),
            &SerializeArmPositionPayload,
            &DeserializeArmPositionPayload
    );
}

BCL_STATUS InitializeSetArmPositionPacket(
        BclPacket *pkt,
        ArmPositionPayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_ARM_POS,
            payload,
            6 * sizeof(int8_t),
            &SerializeArmPositionPayload,
            &DeserializeArmPositionPayload
    );
}

BCL_STATUS InitializeQueryTurretPositionPacket(
        BclPacket *             pkt
)
{
    return InitializeBclPacket(
            pkt,
            QUERY_TURRET_POS,
            NULL,
            0,
            NULL,
            NULL
    );
}

BCL_STATUS InitializeReportTurretPositionPacket(
        BclPacket *             pkt,
        TurretPositionPayload * payload
)
{
    return InitializeBclPacket(
            pkt,
            REPORT_TURRET_POS,
            payload,
            2 * sizeof(int8_t),
            &SerializeTurretPositionPayload,
            &DeserializeTurretPositionPayload
    );
}

BCL_STATUS InitializeSetTurretPositionPacket(
        BclPacket *pkt,
        TurretPositionPayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_TURRET_POS,
            payload,
            2 * sizeof(int8_t),
            &SerializeTurretPositionPayload,
            &DeserializeTurretPositionPayload
    );
}

BCL_STATUS InitializeFreezeTurretPacket(
        BclPacket *             pkt,
        uint8_t *               payload
)
{
    return InitializeBclPacket(
            pkt,
            FREEZE_TURRET,
            payload,
            sizeof(uint8_t),
            &SerializeFreezeTurretPayload,
            &DeserializeFreezeTurretPayload
    );
}

BCL_STATUS InitializeStartCarHornPacket(
        BclPacket *             pkt,
        uint16_t *              payload
)
{
    return InitializeBclPacket(
            pkt,
            START_CAR_HORN,
            payload,
            sizeof(uint16_t),
            &SerializeCarHornPayload,
            &DeserializeCarHornPayload
    );
}

BCL_STATUS InitializeSoilDoorPayloadPacket(
    BclPacket *             pkt,
    SoilDoorPayload *       payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_SOIL_DOOR_SPEED,
            payload,
            sizeof(int8_t),
            &SerializeSoilDoorPayload,
            &DeserializeSoilDoorPayload
    );
}

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

    if (length < (sizeof(uint8_t) + 6 * sizeof(int8_t)))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (const AllWheelSpeedPayload *)payload;
    buffer[FRONT_LEFT_WHEEL] = awsp->front_left;
    buffer[MIDDLE_LEFT_WHEEL] = awsp->middle_left;
    buffer[BACK_LEFT_WHEEL] = awsp->back_left;
    buffer[FRONT_RIGHT_WHEEL] = awsp->front_right;
    buffer[MIDDLE_RIGHT_WHEEL] = awsp->middle_right;
    buffer[BACK_RIGHT_WHEEL] = awsp->back_right;

    if (bytes_written)
        *bytes_written = sizeof(uint8_t) + 6 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS  SerializeArmPositionPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const ArmPositionPayload *app;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < (6 * sizeof(int8_t)))
        return BCL_BUFFER_TOO_SMALL;

    app = (const ArmPositionPayload *)payload;

    buffer[TURNTABLE_INDEX] = app->turntable;
    buffer[HUMERUS_INDEX] = app->humerus;
    buffer[FOREARM_INDEX] = app->forearm;
    buffer[WRIST_UP_DOWN_INDEX] = app->wrist_up_down;
    buffer[WRIST_ROT_INDEX] = app->wrist_rot;
    buffer[CLAW_INDEX] = app->claw;

    if (bytes_written)
        *bytes_written = 6 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeTurretPositionPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const TurretPositionPayload *tpp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    tpp = (const TurretPositionPayload *)payload;
    buffer[0] = tpp->pan;
    buffer[1] = tpp->tilt;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeFreezeTurretPayload (
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const uint8_t * distance;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint8_t))
        return BCL_BUFFER_TOO_SMALL;

    distance = (uint8_t*)payload;
    buffer[0] = *distance;

    if(bytes_written)
        *bytes_written = sizeof(uint8_t);

    return BCL_OK;
}

BCL_STATUS SerializeCarHornPayload (
        const BclPayloadPtr payload,
        uint8_t *           buffer,
        uint8_t             length,
        uint8_t *           bytes_written
)
{
    const uint16_t * time;

    if(!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if(length < sizeof(uint8_t))
        return BCL_BUFFER_TOO_SMALL;

    time = (const uint16_t*)payload;
    buffer[0] = (uint8_t)(*time & 0xFF);
    buffer[1] = (uint8_t)(*time >> 8);

    if(bytes_written)
        *bytes_written = sizeof(uint16_t);

    return BCL_OK;
}


BCL_STATUS SerializeSoilDoorPayload (
    const BclPayloadPtr payload,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
)
{
    const int8_t * position;

    if(!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if(length < sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    position = (const int8_t *)payload;
    buffer[0] = *position;

    if(bytes_written)
        *bytes_written = sizeof(int8_t);

    return BCL_OK;
}

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

    if (length < sizeof(uint8_t) + 6 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (AllWheelSpeedPayload *)payload;
    awsp->front_left = buffer[FRONT_LEFT_WHEEL];
    awsp->middle_left = buffer[MIDDLE_LEFT_WHEEL];
    awsp->back_left = buffer[BACK_LEFT_WHEEL];
    awsp->front_right = buffer[FRONT_RIGHT_WHEEL];
    awsp->middle_right = buffer[MIDDLE_RIGHT_WHEEL];
    awsp->back_right = buffer[BACK_RIGHT_WHEEL];

    if (bytes_read)
        *bytes_read = sizeof(uint8_t) + 6 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeArmPositionPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    ArmPositionPayload *app;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 6 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    app = (ArmPositionPayload *)payload;
    app->turntable = buffer[TURNTABLE_INDEX];
    app->humerus = buffer[HUMERUS_INDEX];
    app->forearm = buffer[FOREARM_INDEX];
    app->wrist_up_down = buffer[WRIST_UP_DOWN_INDEX];
    app->wrist_rot = buffer[WRIST_ROT_INDEX];
    app->claw = buffer[CLAW_INDEX];

    if (bytes_read)
        *bytes_read = 6 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeTurretPositionPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    TurretPositionPayload *tdp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    tdp = (TurretPositionPayload *)payload;
    tdp->pan = buffer[0];
    tdp->tilt = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeFreezeTurretPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    uint8_t * distance;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint8_t))
        return BCL_BUFFER_TOO_SMALL;

    distance = (uint8_t*)payload;
    (*distance) = (*buffer);

    if(bytes_read)
        *bytes_read = sizeof(uint8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeCarHornPayload(
        BclPayloadPtr            payload,
        const uint8_t *          buffer,
        uint8_t                  length,
        uint8_t *                bytes_read
)
{
    uint16_t * time;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint16_t))
        return BCL_BUFFER_TOO_SMALL;

    time = (uint16_t *)payload;
    *time = (buffer[1] << 8) | buffer[0];

    if(bytes_read)
        *bytes_read = sizeof(uint16_t);

    return BCL_OK;

}

BCL_STATUS DeserializeSoilDoorPayload (
    BclPayloadPtr       payload,
    const uint8_t *     buffer,
    uint8_t             length,
    uint8_t *           bytes_read
){
    int8_t * position;
    
    if(!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if(length < sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    position = (int8_t *)payload;
    *position = buffer[0];

    if(bytes_read)
        *bytes_read = sizeof(int8_t);

    return BCL_OK;
}

