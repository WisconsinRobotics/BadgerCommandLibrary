#if ROBOT == Ascent
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
    int8_t front_left;
    int8_t middle_left;
    int8_t back_left;
    int8_t front_right;
    int8_t middle_right;
    int8_t back_right;
} AllWheelSpeedPayload;

typedef struct ArmPositionPayload
{
    int8_t turntable;
    int8_t humerus;
    int8_t forearm;
    int8_t wrist_up_down;
    int8_t wrist_rot;
    int8_t claw;
} ArmPositionPayload;

typedef struct TurretPositionPayload
{
    int8_t pan;
    int8_t tilt;
} TurretPositionPayload;

typedef struct SoilDoorPayload
{
    int8_t position;
} SoilDoorPayload;

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

BCL_STATUS InitializeFreezeTurretPacket(
    BclPacket *             pkt,
    uint8_t *               payload
);

BCL_STATUS InitializeStartCarHornPacket(
    BclPacket *             pkt,
    uint16_t *              payload
);

BCL_STATUS InitializeSoilDoorPayloadPacket(
    BclPacket *             pkt,
    SoilDoorPayload *       payload
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

BCL_STATUS SerializeFreezeTurretPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeCarHornPayload (
    const BclPayloadPtr payload,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
);

BCL_STATUS SerializeSoilDoorPayload (
    const BclPayloadPtr payload,
    uint8_t *           buffer,
    uint8_t             length,
    uint8_t *           bytes_written
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

BCL_STATUS DeserializeFreezeTurretPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

BCL_STATUS DeserializeCarHornPayload(
   BclPayloadPtr            payload,
   const uint8_t *          buffer,
   uint8_t                  length,
   uint8_t *                bytes_read
);

BCL_STATUS DeserializeSoilDoorPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

#ifdef __cplusplus
}
#endif

#endif
#endif