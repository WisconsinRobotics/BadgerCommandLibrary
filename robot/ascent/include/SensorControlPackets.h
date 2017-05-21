#ifndef _SENSOR_CONTROL_PACKETS_H
#define _SENSOR_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"
#include "AscentCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Payload structs */

typedef struct GpsPayload
{
    int16_t lat_degrees;
    int16_t lat_minutes;
    int16_t lat_seconds; // (tenths of a second)
    int16_t long_degrees;
    int16_t long_minutes;
    int16_t long_seconds; // (tenths of a second)
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

BCL_STATUS InitializeReportGPSPacket (
    BclPacket *             pkt,
    GpsPayload *            payload
);

BCL_STATUS InitializeSetGPSPacket (
    BclPacket *             pkt,
    GpsPayload *            payload
);

BCL_STATUS InitializeQuerySoilPacket (
    BclPacket *             pkt
);

BCL_STATUS InitializeReportSoilPacket (
    BclPacket *             pkt,
    SoilPayload *           payload
);

BCL_STATUS InitializeQueryIMUPacket(
    BclPacket *             pkt
);

BCL_STATUS InitializeReportIMUPacket(
    BclPacket *             packet,
    uint16_t *            payload
);

BCL_STATUS InitializeCalibrateIMUPacket(
    BclPacket *             packet,
    uint16_t *   payload
);

BCL_STATUS InitializeByteDisplayPacket(
    BclPacket *             packet,
    uint8_t *               payload
);

BCL_STATUS InitializeQueryMicroscopePacket(
    BclPacket *             pkt
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

BCL_STATUS SerializeIMUPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written
);

BCL_STATUS SerializeCalibrateIMUPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written
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

BCL_STATUS DeserializeIMUPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read
);

BCL_STATUS DeserializeCalibrateIMUPayload(
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
