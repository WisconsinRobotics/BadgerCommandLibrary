#if ROBOT == Atlas
#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "AtlasCommon.h"

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
		int8_t back_left;
		int8_t front_right;
		int8_t back_right;
	} AllWheelSpeedPayload;

/* Initialization function definitions */
	BCL_STATUS InitializeSetTankDriveSpeedPacket(
		BclPacket *pkt,
		TankDrivePayload *payload
	);

	BCL_STATUS InitializeSetAllWheelSpeedPacket(
		BclPacket *pkt,
		AllWheelSpeedPayload *payload
	);

/* Serialization function definitions */
	BCL_STATUS SerializeTankDriveSpeedPayload(
		const BclPayloadPtr     payload,
		uint8_t *               buffer,
		uint8_t                 length,
		uint8_t *               bytes_written
	);

	BCL_STATUS SerializeAllWheelSpeedPayload(
		const BclPayloadPtr     payload,
		uint8_t *               buffer,
		uint8_t                 length,
		uint8_t *               bytes_written
	);

/* Deserialization function definitions */
	BCL_STATUS DeserializeTankDriveSpeedPayload(
		BclPayloadPtr           payload,
		const uint8_t *         buffer,
		uint8_t                 length,
		uint8_t *               bytes_read
	);

	BCL_STATUS DeserializeAllWheelSpeedPayload(
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