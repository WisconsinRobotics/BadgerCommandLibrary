#ifndef _SENSOR_CONTROL_PACKETS_H
#define _SENSOR_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

#define QUERY_GPS          0x50
#define QUERY_SOIL         0x51

#define REPORT_GPS         0x58
#define REPORT_SOIL        0x59

#define REPORT_IMU 0x5A
#define QUERY_IMU 0x5B

#define BYTE_DISPLAY_OPCODE 0x11

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

/* Payload Request Enums*/
typedef enum
{
    X_ACCEL = 0x01, //00000001
    Y_ACCEL = 0x02, //00000010
    Z_ACCEL = 0x04, //00000100
    X_ORIENT = 0x08, //00001000
    Y_ORIENT = 0x10,//00010000
    Z_ORIENT = 0x20 //00100000
}IMU_Measurement;

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
BCL_STATUS InitializeReportIMUPacket(
        BclPacket* packet,
        float* payload
);
BCL_STATUS InitializeQueryIMUPacker(
        BclPacket* packet,
        uint8_t* payload
);
BCL_STATUS InitializeByteDisplayPacket(
        BclPacket* packet,
        uint8_t* payload
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

BCL_STATUS SerializeIMUReportPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written
);

BCL_STATUS SerializeIMUQueryPayload(
        const BclPayloadPtr payload,
        uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_written
);

BCL_STATUS SerializeByteDisplayPayload(
        const BclPayloadPtr payload,
        uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_written
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

BCL_STATUS DeserializeIMUReportPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read
);

BCL_STATUS DeserializeIMUQueryPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read
);

BCL_STATUS DeserializeByteDisplayPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read
);

#ifdef __cplusplus
}
#endif

#endif
