#include "SensorControlPackets.h"

BCL_STATUS InitializeQueryGPSPacket (
	BclPacket * pkt) {
	
	return InitializeBclPacket (
		pkt,
		QUERY_GPS,
		NULL,
		0,
		NULL,
		NULL);
	}
	
BCL_STATUS InitializeQuerySoilPacket (
	BclPacket* pkt) {
	
	return InitializeBclPacket (
		pkt,
		QUERY_SOIL,
		NULL,
		0,
		NULL,
		NULL);
	}
	
BCL_STATUS  InitializeReportGPSPacket (
	BclPacket * pkt, GpsPayload * payload) {
	
	return InitializeBclPacket (
		pkt,
		REPORT_GPS,
		payload,
		sizeof(payload),
		&SerializeGPSPayload,
		&DeserializeGPSPayload);
	}
	
BCL_STATUS InitializeReportSoilPacket (
	BclPacket * pkt, SoilPayload * payload) {

	return InitializeBclPacket (
		pkt,
		REPORT_SOIL,
		payload,
		sizeof(payload),
		&SerializeSoilPayload,
		&DeserializeSoilPayload);
	}
	
//Serialization
BCL_STATUS SerializeGPSPayload (
    const BclPayloadPtr  payload,
    uint8_t * 			 buffer,
    uint8_t				 length,
    uint8_t * 			 bytes_written) {
    
    const GpsPayload *ptr;
    
    //inputs good?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
        
    // enough size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    ptr = (uint8_t *)(payload);
    buffer[0] = ptr->lat_degrees;
    buffer[1] = ptr->lat_degrees >> 8;
    buffer[2] = ptr->lat_minutes;
    buffer[3] = ptr->lat_minutes >> 8;
    buffer[4] = ptr->lat_seconds;
	buffer[5] = ptr->lat_seconds >> 8;
	buffer[6] = ptr->long_degrees;
	buffer[7] = ptr->long_degrees >> 8;
	buffer[8] = ptr->long_minutes;
	buffer[9] = ptr->long_minutes >> 8;
	buffer[10] = ptr->long_seconds;
	buffer[11] = ptr->long_seconds >> 8;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
    }

BCL_STATUS SerializeSoilPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written) {
    
    const SoilPayload *ptr;
    
    //inputs?
    if (!buffer || !payload)
    	return BCL_INVALID_PARAMETER;
    	
    //size?
    if (length < 2 * sizeof(int8_t))
    	return BCL_BUFFER_TOO_SMALL;
    	
    ptr = (SoilPayload *)(payload);
    buffer[0] = ptr->temperature;
    buffer[1] = ptr->temperature >> 8;
    buffer[2] = ptr->humidity;
    buffer[3] = ptr->humidity >> 8;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
    }


/* Deserialization functions */

BCL_STATUS DeserializeGPSPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read) {

    GpsPayload *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (GpsPayload *) payload;
    ptr->lat_degrees =  buffer[1];
    ptr->lat_degrees = (ptr->lat_degrees << 8) + buffer[0];
    ptr->lat_degrees = buffer[0];
    
    ptr->lat_minutes = buffer[3];
    ptr->lat_minutes = (ptr->lat_minutes << 8) + buffer[2];
    ptr->lat_minutes = buffer[2];
    
    ptr->lat_seconds = buffer[5];
    ptr->lat_seconds = (ptr->lat_seconds << 8) + buffer[4];
    ptr->lat_seconds = buffer[4];
   
    ptr->long_degrees = buffer[7];
    ptr->long_degrees = (ptr->long_degrees << 8) + buffer[6];    
	ptr->long_degrees = buffer[6];
	
	ptr->long_minutes = buffer[9];
	ptr->long_minutes = (ptr->long_minutes << 8) + buffer[8];
	ptr->long_degrees = buffer[8];
	
	ptr->long_seconds = buffer[11];
	ptr->long_seconds = (ptr->long_seconds << 8) + buffer[10];
	ptr->long_seconds = buffer[10];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeSoilPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read) {
    
    SoilPayload *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (SoilPayload *) payload;
    ptr->temperature = buffer[1];
    ptr->temperature = (ptr->temperature << 8) + buffer[0];
    ptr->temperature = buffer[0];
    
    ptr->humidity = buffer[3];
    ptr->humidity = (ptr->humidity << 8) + buffer[2];
    ptr->humidity = buffer[2];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}