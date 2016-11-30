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
    
    const BclPayloadPtr *ptr;
    
    //inputs good?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
        
    // enough size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    ptr = (const BclPayloadPtr *)(payload);
    buffer[0] = ptr->left;
    buffer[1] = ptr->right;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
    }

BCL_STATUS SerializeSoilPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written) {
    
    const BclPayloadPtr *ptr;
    
    //inputs?
    if (!buffer || !payload)
    	return BCL_INVALID_PARAMETER;
    	
    //size?
    if (length < 2 * sizeof(int8_t))
    	return BCL_BUFFER_TOO_SMALL;
    	
    ptr = (const BclPayloadPtr *)(payload);
    buffer[0] = ptr->left;
    buffer[1] = ptr->right;

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

    BclPayloadPtr *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (BclPayloadPtr *) payload;
    ptr->left = buffer[0];
    ptr->right = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeSoilPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read) {
    
    BclPayloadPtr *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (BclPayloadPtr *) payload;
    ptr->left = buffer[0];
    ptr->right = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}