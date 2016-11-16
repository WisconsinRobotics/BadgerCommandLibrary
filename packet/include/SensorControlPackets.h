#ifndef _SENSOR_CONTROL_PACKETS_H
#define _SENSOR_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

#define GPS_QUERY          0x50
#define TEMPERATURE_QUERY  0x51
#define HUMIDITY_QUERY     0x52

#define GPS_REPORT         0x58
#define TEMPERATURE_REPORT 0x59
#define HUMUDITY_REPORT    0x5A

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GpsData {
	int16_t lat_degrees,
	int16_t lat_minutes,
	int16_t lat_seconds,
	int16_t long_degrees,
	int16_t long_minutes,
	int16_t long_seconds
};

BCL_STATUS InitializeGPSQueryPacket (
	BclPacket *pkt
);

BCL_STATUS InitializeTemperatureQueryPacket (
	BclPacket *pkt
);

BCL_STATUS InitializeHumidityQueryPacket (
	BclPacket *pkt
);

BCL_STATUS InitializeGPSReportPacket (
	BclPacket *pkt,
	GpsData *gpsData
);

BCL_STATUS InitializeTemperatureReportPacket (
	BclPacket *pkt,
	int temperature
);

BCL_STATUS InitializeHumidityReportPacket (
	BclPacket *pkt,
	int humidity
);

#ifdef __cplusplus
}
#endif

#endif