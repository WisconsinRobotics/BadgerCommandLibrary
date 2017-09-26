#include "SensorControlPackets.h"
#include <stddef.h>


//Initilizing GPS Packet
BCL_STATUS InitializeQueryGPSPacket(BclPacket * pkt)
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

BCL_STATUS InitializeReportGPSPacket(BclPacket *pkt, GpsPayload *payload)
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

BCL_STATUS InitializeSetGPSPacket(BclPacket *pkt, GpsPayload *payload)
{
    return InitializeBclPacket(
            pkt,
            SET_GPS,
            payload,
            sizeof(GpsPayload),
            &SerializeGPSPayload,
            &DeserializeGPSPayload
    );
}

//Initializing IMU Packet
BCL_STATUS InitializeQueryIMUPacket(BclPacket *pkt)
{
    return InitializeBclPacket(
            pkt,
            QUERY_IMU,
            NULL,
            0,
            NULL,
            NULL
    );
}

BCL_STATUS InitializeReportIMUPacket(BclPacket* packet, ImuPayload* payload)
{
    return InitializeBclPacket(
            packet,
            REPORT_IMU,
            payload,
            6 * sizeof(int16_t),
            &SerializeIMUPayload,
            &DeserializeIMUPayload);
}

BCL_STATUS InitializeCalibrateIMUPacket(BclPacket* packet, CalibrateImuPayload* payload)
{
    return InitializeBclPacket(
            packet,
            CALIBRATE_IMU,
            payload,
            2 * sizeof(int16_t),
            &SerializeCalibrateIMUPayload,
            &DeserializeCalibrateIMUPayload);
}

//GPS Payload serialization function
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

//IMU Payload serialization function
BCL_STATUS SerializeIMUPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written)
{
    const ImuPayload* ptr;
    //inputs good?
    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length < 6 * sizeof(int16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (ImuPayload*)payload;
    //The order of the data in the buffer is 1) x accel, 2) y accel, 3) z accell,
    //4) x orient, 5)y orient , 6) z orient
    //and the data is big endian
    //x accel
    buffer[0] = 0;
    buffer[1] = 0;
    //y accel
    buffer[2] = 0;
    buffer[3] = 0;
    //z accel
    buffer[4] = 0;
    buffer[5] = 0;
    //x orient
    buffer[6] = 0;
    buffer[7] = 0;
    //y orient
    buffer[8] = (ptr->y_orient) >> 8;
    buffer[9] = ptr->y_orient;
    //z orient
    buffer[10] = (ptr->z_orient) >> 8;
    buffer[11] = ptr->z_orient;

    if(bytes_written)
        *bytes_written = 6 * sizeof(int16_t);

    return BCL_OK;
}

BCL_STATUS SerializeCalibrateIMUPayload(
        const BclPayloadPtr payload,
        uint8_t * buffer,
        uint8_t length,
        uint8_t * bytes_written)
{
    const CalibrateImuPayload* ptr;

    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    if(length < 2 * sizeof(int16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (CalibrateImuPayload*)payload;

    buffer[0] = ptr->x_offset >> 8;
    buffer[1] = ptr->x_offset & 0xFF;
    buffer[2] = ptr->y_offset >> 8;
    buffer[3] = ptr->y_offset & 0xFF;

    if(bytes_written)
        (*bytes_written) = 2 * sizeof(int16_t);

    return BCL_OK;
}

//GPS Payload deserialization function
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

//IMU Payload deserialization function
BCL_STATUS DeserializeIMUPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read)
{
    ImuPayload* ptr;

    //inputs good?
    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length <  sizeof(uint16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (ImuPayload*)payload;
    //The order of the data in the buffer is 1) x accel, 2) y accel, 3) z accell,
    //4) x orient, 5)y orient , 6) z orient
    //and the data is big endian
    ptr->x_accel = (buffer[0] << 8) | buffer[1];
    ptr->y_accel = (buffer[2] << 8) | buffer[3];
    ptr->z_accel = (buffer[4] << 8) | buffer[5];
    ptr->x_orient = (buffer[6] << 8) | buffer[7];
    ptr->y_orient = (buffer[8] << 8) | buffer[9];
    ptr->z_orient = (buffer[10] << 8) | buffer[11];

    if(bytes_read)
        (*bytes_read) = 6 * sizeof(int16_t);

    return BCL_OK;
}

BCL_STATUS DeserializeCalibrateIMUPayload(
        BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read)
{
    CalibrateImuPayload* ptr;

    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length < 2 * sizeof(int16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (CalibrateImuPayload*) payload;
    ptr->x_offset = ((buffer[0] << 8) | buffer[1]);
    ptr->y_offset = ((buffer[2] << 8) | buffer[3]);

    if(bytes_read)
        (*bytes_read) = 2 * sizeof(int16_t);

    return BCL_OK;
}