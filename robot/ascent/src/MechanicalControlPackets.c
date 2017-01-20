#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

BCL_STATUS InitializeSetTankDriveSpeedPacket (
    BclPacket *pkt,
    TankDrivePayload *payload
    )
{
    return InitializeBclPacket (
        pkt,
        SET_TANK_DRIVE_SPEED,
        payload,
        2 * sizeof(int8_t),
        &SerializeTankDriveSpeedPayload,
        &DeserializeTankDriveSpeedPayload
    );
}

BCL_STATUS InitializeSetAllWheelSpeedPacket (
    BclPacket *pkt,
    AllWheelSpeedPayload *payload
    )
{
    return InitializeBclPacket (
        pkt,
        SET_ALL_WHEEL_SPEED,
        payload,
        sizeof(uint8_t) + NUMBER_WHEELS * sizeof(int8_t),
        &SerializeAllWheelSpeedPayload,
        &DeserializeAllWheelSpeedPayload
    );
}

BCL_STATUS InitializeQueryArmPositionPacket (
    BclPacket *pkt
    )
{
    return InitializeBclPacket (
        pkt,
        QUERY_ARM_POS,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportArmPositionPacket (
    BclPacket               *pkt,
    ArmPositionPayload      *payload
    )
{
    return InitializeBclPacket (
        pkt,
        REPORT_ARM_POS,
        payload,
        sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(uint8_t),
        &SerializeArmPositionPayload,
        &DeserializeArmPositionPayload
    );
}

BCL_STATUS InitializeSetArmPositionPacket (
    BclPacket *pkt,
    ArmPositionPayload *payload
    )
{
    return InitializeBclPacket(
        pkt,
        SET_ARM_POS,
        payload,
        sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(uint8_t),
        &SerializeArmPositionPayload,
        &DeserializeArmPositionPayload
    );
}

BCL_STATUS InitializeQueryTurretPositionPacket (
    BclPacket *             pkt
    )
{
    return InitializeBclPacket (
        pkt,
        QUERY_TURRET_POS,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportTurretPositionPacket (
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

BCL_STATUS InitializeSetTurretPositionPacket (
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

BCL_STATUS SerializeTankDriveSpeedPayload (
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

    if (length < (sizeof(uint8_t) + NUMBER_WHEELS * sizeof(int8_t)))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (const AllWheelSpeedPayload *)payload;
    buffer[0] = awsp->numWheels;
    memcpy(buffer + 1, awsp->wheelSpeeds, NUMBER_WHEELS * sizeof(int8_t));

    if (bytes_written)
        *bytes_written = sizeof(uint8_t) + NUMBER_WHEELS * sizeof(int8_t);

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

    if (length < (sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(uint8_t)))
        return BCL_BUFFER_TOO_SMALL;

    app = (const ArmPositionPayload *) payload;

    buffer[0] = app->numArmPositions;
    memcpy(buffer + 1, app->armPositions, NUMBER_ARM_MOTOR_POSITONS * sizeof(uint8_t));

    if (bytes_written)
        *bytes_written = sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeTurretPositionPayload (
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

    tpp = (const TurretPositionPayload *) payload;
    buffer[0] = tpp->pan;
    buffer[1] = tpp->tilt;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

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
    
    tdp = (TankDrivePayload *) payload;
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

    if (length < sizeof(uint8_t) + NUMBER_WHEELS * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    awsp = (AllWheelSpeedPayload *) payload;
    if (!awsp->wheelSpeeds)
        return BCL_INVALID_PARAMETER;

    awsp->numWheels = buffer[0];
    if (awsp->numWheels != NUMBER_WHEELS)
        return BCL_BAD_PAYLOAD;

    memcpy(awsp->wheelSpeeds, buffer + 1, NUMBER_WHEELS * sizeof(int8_t));

    if (bytes_read)
        *bytes_read = sizeof(uint8_t) + NUMBER_WHEELS * sizeof(int8_t);

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

    if (length < sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    app = (ArmPositionPayload *)payload;
    if (!app->numArmPositions)
        return BCL_INVALID_PARAMETER;

    app->numArmPositions = buffer[0];
    if (app->numArmPositions != NUMBER_ARM_MOTOR_POSITONS)
        return BCL_BAD_PAYLOAD;

    memcpy(app->armPositions, buffer + 1, NUMBER_ARM_MOTOR_POSITONS * sizeof(int8_t));

    if (bytes_read)
        *bytes_read = sizeof(uint8_t) + NUMBER_ARM_MOTOR_POSITONS * sizeof(int8_t);

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

    tdp = (TurretPositionPayload *) payload;
    tdp->pan = buffer[0];
    tdp->tilt = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}
