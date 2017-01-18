#include "SensorControlPackets.h"
#include <stddef.h>


BCL_STATUS InitializeQueryGPSPacket (
    BclPacket * pkt
    ) 
{
    return InitializeBclPacket (
        pkt,
	    QUERY_GPS,
        NULL,
        0,
        NULL,
        NULL
    );
}
	
BCL_STATUS InitializeQuerySoilPacket (
	BclPacket * pkt
    ) 
{
	return InitializeBclPacket (
		pkt,
		QUERY_SOIL,
		NULL,
		0,
		NULL,
		NULL
    );
}
	
BCL_STATUS  InitializeReportGPSPacket (
	BclPacket * pkt,
    GpsPayload * payload
    ) 
{
    return InitializeBclPacket (
        pkt,
        REPORT_GPS,
        payload,
        sizeof(GpsPayload),
        &SerializeGPSPayload,
        &DeserializeGPSPayload
    );
}
	
BCL_STATUS InitializeReportSoilPacket (
	BclPacket * pkt,
    SoilPayload * payload
    )
{
	return InitializeBclPacket (
	        pkt,
	        REPORT_SOIL,
	        payload,
	        sizeof(SoilPayload),
	        &SerializeSoilPayload,
	        &DeserializeSoilPayload
	    );
	}

BCL_STATUS InitializeReportIMUPacket(BclPacket* packet, float* payload)
{
    return InitializeBclPacket(
            packet,
            REPORT_IMU,
            payload,
            sizeof(float),
            &SerializeIMUPayload,
            &DeserializeIMUPayload);
}

BCL_STATUS InitializeByteDisplayPacket(BclPacket* packet, uint8_t* payload)
{
    return InitializeBclPacket(packet,
            BYTE_DISPLAY_OPCODE,
            payload,
            sizeof(uint8_t),
            &SerializeByteDisplayPayload,
            &DeserializeByteDisplayPayload);
}
	
//Serialization
BCL_STATUS SerializeGPSPayload (
    const BclPayloadPtr  payload,
    uint8_t * 			 buffer,
    uint8_t				 length,
    uint8_t * 			 bytes_written
    )
{
    const GpsPayload *ptr;
    
    //inputs good?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
        
    // enough size?
    if (length <  6 * sizeof(int16_t))
        return BCL_BUFFER_TOO_SMALL;

    ptr = (const GpsPayload *)(payload);
    buffer[0] = ptr->lat_degrees >> 8;
    buffer[1] = ptr->lat_degrees & 0xFF;
    buffer[2] = ptr->lat_minutes >> 8;
    buffer[3] = ptr->lat_minutes & 0xFF;
    buffer[4] = ptr->lat_seconds >> 8;
    buffer[5] = ptr->lat_seconds & 0xFF;
    buffer[6] = ptr->long_degrees >> 8;
    buffer[7] = ptr->long_degrees & 0xFF;
    buffer[8] = ptr->long_minutes >> 8;
    buffer[9] = ptr->long_minutes & 0xFF;
    buffer[10] = ptr->long_seconds >> 8;
    buffer[11] = ptr->long_seconds & 0xFF;

    if (bytes_written)
        *bytes_written = 6 * sizeof(int16_t);

    return BCL_OK;
}

BCL_STATUS SerializeSoilPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
    )
{
    const SoilPayload *ptr;
    
    //inputs?
    if (!buffer || !payload)
    	return BCL_INVALID_PARAMETER;
    	
    //size?
    if (length < 2 * sizeof(int8_t))
    	return BCL_BUFFER_TOO_SMALL;
    	
    ptr = (SoilPayload *)(payload);
    buffer[0] = ptr->temperature >> 8;
    buffer[1] = ptr->temperature & 0xFF;
    buffer[2] = ptr->humidity >> 8;
    buffer[3] = ptr->humidity & 0xFF;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeIMUPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written)
{
    //inputs good?
    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length < sizeof(float))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    //Break the value of the float into four bytes for serialization
    uint32_t payloadAsInt = *(uint32_t*)payload;
    buffer[0] = (payloadAsInt & 0xFF);//The least significant byte
    buffer[1] = (payloadAsInt & 0xFF00) >> 8;//The second least significant byte
    buffer[2] = (payloadAsInt & 0xFF0000) >> 16;//The third least significant byte
    buffer[3] = (payloadAsInt & 0xFF000000) >> 24;//The most significant byte

    if(bytes_written)
        *bytes_written = sizeof(float);

    return BCL_OK;
}

BCL_STATUS SerializeByteDisplayPayload(
        const BclPayloadPtr payload,
        uint8_t* buffer,
        uint8_t length,
        uint8_t* bytesWritten)
{
    //Make sure there is only one byte of data
    if(length != 1)
    {
        return BCL_PAYLOAD_SIZE_MISMATCH;
    }

    //The buffer will just be a string of 8 bits indicating which LED to turn on
    //so, just copy the buffer to the payload
    *buffer = *(uint8_t*)payload;

    *bytesWritten = 1;

    return BCL_OK;
}

/* Deserialization functions */

BCL_STATUS DeserializeGPSPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
    ) 
{
    GpsPayload *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 6 * sizeof(int16_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (GpsPayload *) payload;
    ptr->lat_degrees =  (buffer[0] << 8) | (buffer[1]);
    ptr->lat_minutes = (buffer[2] << 8) | (buffer[3]);
    ptr->lat_seconds = (buffer[4] << 8) | (buffer[5]);
    ptr->long_degrees = (buffer[6] << 8) | (buffer[7]);
    ptr->long_minutes = (buffer[8] << 8) | (buffer[9]);
    ptr->long_seconds = (buffer[10] << 8) | (buffer[11]);

    if (bytes_read)
        *bytes_read = 6 * sizeof(int16_t);

    return BCL_OK;
}

BCL_STATUS DeserializeSoilPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
    )
{
    SoilPayload *ptr;

	//inputs?
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

	//size?
    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;
    
    ptr = (SoilPayload *) payload;
    ptr->temperature = (buffer[0] << 8) | (buffer[1]);
    ptr->humidity = (buffer[2] << 8) | (buffer[3]);

    if (bytes_read)
        *bytes_read = 12 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeIMUPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read)
{
    //inputs good?
    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length < sizeof(float))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    //Recombine the payload into a float
    uint32_t* payloadAsInt = (uint32_t*)payload;
    //The lowest array value of the buffer is the least significant bit
    (*payloadAsInt) = (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | (buffer[0]);

    if(bytes_read)
        (*bytes_read) = sizeof(float);

    return BCL_OK;
}

BCL_STATUS DeserializeByteDisplayPayload(BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytesRead)
{
    //Make sure there is only one byte of data
    if(length != 1)
    {
        return BCL_PAYLOAD_SIZE_MISMATCH;
    }

    //The payload will just be a string of 8 bits indicating which LED to turn on
    //so, just copy the payload to the buffer
    *(uint8_t*)payload = *buffer;

    *bytesRead = 1;

    return BCL_OK;
}

