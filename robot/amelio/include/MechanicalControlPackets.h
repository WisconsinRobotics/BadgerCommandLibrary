#if ROBOT == Amelio
#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "Common.h"

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
		int8_t mid_left;
		int8_t back_left;
		int8_t front_right;
		int8_t mid_right;
		int8_t back_right;
	} AllWheelSpeedPayload;

    typedef struct ArmSpeedPayload
    {
        int8_t turntable;
        int8_t humerus;
        int8_t forearm;
        int8_t wrist_up_down;
        int8_t wrist_rot;
        int8_t claw;
        int8_t sliding;
    } ArmPayload;

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

	typedef struct CameraMastPayload
	{
	    int8_t pan;
	    int8_t tilt;
	} CameraMastPayload;

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

/* Deserialization function definitions */
	BCL_STATUS DeserializeAllWheelSpeedPayload(
		BclPayloadPtr   		payload,
		const uint8_t *			buffer,
		uint8_t                 bufferlength,
		uint8_t *               bytes_read
	);

	BCL_STATUS DeserializeTankDriveSpeedPayload(
		BclPayloadPtr           payload,
		const uint8_t *		  	buffer,
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
		const uint8_t *		  	buffer,
		uint8_t                 bufferlength,
		uint8_t *               bytes_read
	);

	BCL_STATUS DeserializeAllRideHeightSpeedPayload(
		BclPayloadPtr   		payload,
		const uint8_t *			buffer,
		uint8_t                 bufferlength,
		uint8_t *               bytes_read
	);

	BCL_STATUS DeserializeCameraMastPayload(
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
