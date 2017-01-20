#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "AscentCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Payload definitions */

typedef struct TankDrivePayload
{
    int8_t left;
    int8_t right;
} TankDrivePayload;

typedef struct AllWheelSpeedPayload
{
    uint8_t numWheels;
    int8_t wheelSpeeds[NUMBER_WHEELS];
} AllWheelSpeedPayload;

typedef struct ArmPositionPayload
{
    uint8_t numArmPositions;
    int8_t armPositions[NUMBER_ARM_MOTOR_POSITONS];
} ArmPositionPayload;

typedef struct TurretPositionPayload
{
    int8_t pan;
    int8_t tilt;
} TurretPositionPayload;

/* Initialization function definitions */

BCL_STATUS InitializeSetTankDriveSpeedPacket(
    BclPacket *             pkt,
    TankDrivePayload *      payload
);

BCL_STATUS InitializeSetAllWheelSpeedPacket (
    BclPacket *             pkt,
    AllWheelSpeedPayload *  payload
);

BCL_STATUS InitializeQueryArmPositionPacket (
	BclPacket *             pkt
);

BCL_STATUS InitializeReportArmPositionPacket (
	BclPacket *             pkt,
    ArmPositionPayload *    payload
);

BCL_STATUS InitializeSetArmPositionPacket(
    BclPacket *             pkt,
    ArmPositionPayload *    payload
);

BCL_STATUS InitializeQueryTurretPositionPacket (
    BclPacket *             pkt
);

BCL_STATUS InitializeReportTurretPositionPacket (
	BclPacket *             pkt,
    TurretPositionPayload * payload
);

BCL_STATUS InitializeSetTurretPositionPacket (
	BclPacket *             pkt,
    TurretPositionPayload * payload
);

/* Serialization function definitions */

BCL_STATUS SerializeTankDriveSpeedPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeAllWheelSpeedPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeArmPositionPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeTurretPositionPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

/* Deserialization function definitions */

BCL_STATUS DeserializeTankDriveSpeedPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read 
);

BCL_STATUS DeserializeAllWheelSpeedPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

BCL_STATUS DeserializeArmPositionPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

BCL_STATUS DeserializeTurretPositionPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

#ifdef __cplusplus
}
#endif

#endif
