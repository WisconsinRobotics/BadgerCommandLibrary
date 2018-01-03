#if ROBOT == Atlas
#ifndef _SENSOR_CONTROL_PACKETS_H
#define _SENSOR_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "AtlasCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

	/* Payload structs */

	typedef struct BatPayload
	{
		int32_t current;
	} BatPayload;

	/* Initialization functions */

	BCL_STATUS InitializeQueryBatPacket(
		BclPacket *				pkt
	);

	BCL_STATUS InitializeReportBatPacket(
		BclPacket *				pkt,
		BatPayload *		payload
	);

	/* Serialization functions */

	BCL_STATUS SerializeBatPayload(
		const BclPayloadPtr payload,
		uint8_t* buffer,
		uint8_t length,
		uint8_t* bytes_written
	);

	/* Deserialization functions */

	BCL_STATUS DeserializeBatPayload(
		BclPayloadPtr payload,
		const uint8_t* buffer,
		uint8_t length,
		uint8_t* bytes_read
	);

#ifdef __cplusplus
}
#endif

#endif
#endif