#ifndef _SENSOR_CONTROL_PACKETS_H
#define _SENSOR_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

#define QUERY_GPS          0x50
#define QUERY_SOIL         0x51

#define REPORT_GPS         0x58
#define REPORT_SOIL        0x59

#ifdef __cplusplus
extern "C" {
#endif

/* Payload structs */

typedef struct GpsPayload
{
	int16_t lat_degrees;
	int16_t lat_minutes;
	int16_t lat_seconds;
	int16_t long_degrees;
	int16_t long_minutes;
	int16_t long_seconds;
} GpsPayload;

typedef struct SoilPayload
{
    int16_t temperature;
    int16_t humidity;
} SoilPayload;

/* Initialization functions */

BCL_STATUS InitializeQueryGPSPacket (
	BclPacket *             pkt
);

BCL_STATUS InitializeQuerySoilPacket (
	BclPacket *             pkt
);

BCL_STATUS InitializeReportGPSPacket (
	BclPacket *             pkt,
	GpsPayload *            payload
);

BCL_STATUS InitializeReportSoilPacket (
	BclPacket *             pkt,
	SoilPayload *           payload
);

/* Serialization functions */

BCL_STATUS SerializeGPSPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeSoilPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

/* Deserialization functions */

BCL_STATUS DeserializeGPSPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

BCL_STATUS DeserializeSoilPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

#ifdef __cplusplus
}
#endif

#endif
