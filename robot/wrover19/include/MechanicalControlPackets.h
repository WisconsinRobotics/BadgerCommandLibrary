#if ROBOT == WRover19
#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Payload definitions */

    // drive motors speed
    typedef struct TankDrivePayload
    {
        int8_t left;
        int8_t right;
    } TankDrivePayload;

    typedef struct AllWheelSpeedPayload
    {
        int8_t front_left;
        int8_t mid_left;
        int8_t back_left;
        int8_t front_right;
        int8_t mid_right;
        int8_t back_right;
    } AllWheelSpeedPayload;

    // arm position
    typedef struct ArmPayload
    {
        int16_t turntable;
        int16_t shoulder;
        int16_t elbow;
        int16_t forearm;
        int16_t wrist_left;
        int16_t wrist_right;
        int16_t claw;
    } ArmPayload;

    // ride height position/speed
    typedef struct RideHeightPayload
    {
        int8_t front;
        int8_t back;
    } RideHeightPayload;

    typedef struct AllRideHeightSpeedPayload
    {
        int8_t front_left;
        int8_t back_left;
        int8_t front_right;
        int8_t back_right;
    } AllRideHeightSpeedPayload;

    // camera mast position
    typedef struct CameraMastPayload
    {
        int8_t pan;
        int8_t tilt;
    } CameraMastPayload;

    // solenoid position control --- NOT USED
    typedef struct SolenoidPayload
    {
        uint16_t duration;
    } SolenoidPayload; 

    // drive motor PID control
    typedef struct __attribute__((__packed__)) PidPayload
    {
        uint32_t p;
        uint32_t i;
        uint32_t d;
        uint8_t addr;
        uint8_t vel;
    } PidPayload;

    // soil door position/speed
    typedef struct DynamixelPositionPayload
    {
        int8_t position;
    } DynamixelPositionPayload;
    
    typedef struct DynamixelSpeedPayload
    {
        int8_t speed;
    } DynamixelSpeedPayload;

    // augur rotational and linear velocities
    typedef struct AugurRotationPayload
    {
        int8_t velocity;
    } AugurRotationPayload;

    typedef struct AugurLinearPayload
    {
        int8_t velocity;
    } AugurLinearPayload;

    // test tube carriage velocity
    typedef struct TestTubePayload
    {
        int8_t velocity;
    } TestTubePayload;

    // soil camera actuator velocity
    typedef struct SoilCamActuatorPayload
    {
        int8_t velocity;
    } SoilCamActuatorPayload;

/* Initialization function definitions */
    BCL_STATUS InitializeSetTankDriveSpeedPacket(
        BclPacket *pkt, TankDrivePayload *payload);

    BCL_STATUS InitializeAllWheelSpeedPacket(
        BclPacket *pkt, AllWheelSpeedPayload *payload);

    BCL_STATUS InitializeQueryArmPositionPacket (
        BclPacket * pkt);

    BCL_STATUS InitializeReportArmPositionPacket (
        BclPacket * pkt, ArmPayload * payload);

    BCL_STATUS InitializeSetArmPositionPacket(
        BclPacket * pkt, ArmPayload * payload);
    
    BCL_STATUS InitializeQueryArmSpeedPacket (
        BclPacket * pkt);

    BCL_STATUS InitializeReportArmSpeedPacket (
        BclPacket * pkt, ArmPayload * payload);

    BCL_STATUS InitializeSetArmSpeedPacket(
        BclPacket * pkt, ArmPayload * payload);

    BCL_STATUS InitializeSetRideHeightSpeedPacket(
        BclPacket *pkt, RideHeightPayload *payload);

    BCL_STATUS InitializeAllRideHeightSpeedPacket(
        BclPacket *pkt, AllRideHeightSpeedPayload *payload);

    BCL_STATUS InitializeSetCameraMastPacket (
        BclPacket *pkt, CameraMastPayload * payload);

    BCL_STATUS InitializeActivateSolenoidPacket(
        BclPacket * pkt, SolenoidPayload * payload);

    BCL_STATUS InitializeQueryPidPacket(
        BclPacket *pkt);

    BCL_STATUS InitializeReportPidPacket(
        BclPacket *pkt, PidPayload *payload);

    BCL_STATUS InitializeSetPidPacket(
        BclPacket *pkt, PidPayload *payload);

    BCL_STATUS InitializeQuerySoilDoorPacket (
        BclPacket * pkt);

    BCL_STATUS InitializeReportSoilDoorPacket (
        BclPacket * pkt, DynamixelPositionPayload * payload);

    BCL_STATUS InitializeSetSoilDoorPacket(
        BclPacket * pkt, DynamixelPositionPayload * payload);

    BCL_STATUS InitializeActivateAugurRotPacket(
        BclPacket *pkt, AugurRotationPayload *payload);

    BCL_STATUS InitializeActivateAugurLinPacket(
        BclPacket *pkt, AugurLinearPayload *payload);

    BCL_STATUS InitializeQueryTestTubePacket (
        BclPacket * pkt);

    BCL_STATUS InitializeReportTestTubePacket (
        BclPacket * pkt, TestTubePayload * payload);

    BCL_STATUS InitializeSetTestTubePacket(
        BclPacket * pkt, TestTubePayload * payload);

    BCL_STATUS InitializeQuerySoilCamPacket (
        BclPacket * pkt);

    BCL_STATUS InitializeReportSoilCamPacket (
        BclPacket * pkt, SoilCamActuatorPayload * payload);

    BCL_STATUS InitializeSetSoilCamPacket(
        BclPacket * pkt, SoilCamActuatorPayload * payload);

/* Serialization function definitions */
    BCL_STATUS SerializeAllWheelSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeTankDriveSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeArmPayload (
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeRideHeightSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeAllRideHeightSpeedPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeCameraMastPayload (
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializePidPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
        );

    BCL_STATUS SerializeDynamixelPositionPayload (
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeAugurRotationPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeAugurLinearPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeTestTubePayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

    BCL_STATUS SerializeSoilCamActuatorPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
    );

/* Deserialization function definitions */
    BCL_STATUS DeserializeAllWheelSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *            buffer,
        uint8_t                 bufferlength,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeTankDriveSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *              buffer,
        uint8_t                 bufferlength,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeArmPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeRideHeightSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *              buffer,
        uint8_t                 bufferlength,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeAllRideHeightSpeedPayload(
        BclPayloadPtr           payload,
        const uint8_t *            buffer,
        uint8_t                 bufferlength,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeCameraMastPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializePidPayload(
        BclPayloadPtr     payload,
        const uint8_t *               buffer,
        uint8_t                 bufferLength,
        uint8_t *               bytes_written
        );

    BCL_STATUS DeserializeDynamixelPositionPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeAugurRotationPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeAugurLinearPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeTestTubePayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
    );

    BCL_STATUS DeserializeSoilCamActuatorPayload(
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
