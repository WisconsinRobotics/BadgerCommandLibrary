#if ROBOT == Atlas
#include "SensorControlPackets.h"
#include <stddef.h>

//Initialization
BCL_STATUS InitializeQueryBatPacket(BclPacket * pkt)
{
	return InitializeBclPacket(
		pkt,
		QUERY_BAT,
		NULL,
		0,
		NULL,
		NULL
	);
}

BCL_STATUS InitializeReportBatPacket(BclPacket * pkt, BatPayload * payload)
{
	return InitializeBclPacket(
		pkt,
		REPORT_BAT,
		payload,
		sizeof(int32_t),
		&SerializeBatPayload,
		&DeserializeBatPayload
	);
}

//Serialization
BCL_STATUS SerializeBatPayload(
	const BclPayloadPtr payload,
	uint8_t * buffer,
	uint8_t length,
	uint8_t * bytes_written)
{

	const BatPayload *ptr;

	//inputs?
	if (!buffer || !payload)
		return BCL_INVALID_PARAMETER;

	//size?
	if (length < 4 * sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	ptr = (BatPayload *)(payload);
	buffer[0] = ptr->current >> 24;
	buffer[1] = ptr->current >> 16;
	buffer[2] = ptr->current >> 8;
	buffer[3] = ptr->current & 0xFF;

	if (bytes_written)
		*bytes_written = 4 * sizeof(int8_t);

	return BCL_OK;
}

/* Deserialization functions */
BCL_STATUS DeserializeBatPayload(
	BclPayloadPtr payload,
	const uint8_t* buffer,
	uint8_t length,
	uint8_t* bytes_read)
{
	BatPayload *ptr;

	//inputs?
	if (!buffer || !payload)
		return BCL_INVALID_PARAMETER;

	//size?
	if (length < 4 * sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	ptr = (BatPayload *)payload;
	ptr->current = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

	if (bytes_read)
		*bytes_read = 4 * sizeof(int8_t);

	return BCL_OK;
}
#endif