#include "SensorControlPackets.h"
#include <stddef.h>


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

BCL_STATUS InitializeQuerySoilPacket(BclPacket * pkt)
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
BCL_STATUS InitializeReportSoilPacket(BclPacket *pkt, SoilPayload *payload)
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

BCL_STATUS InitializeCalibrateIMUPacket(BclPacket* packet, uint16_t* payload)
{
    return InitializeBclPacket(
            packet,
            CALIBRATE_IMU,
            payload,
            sizeof(uint16_t),
            &SerializeCalibrateIMUPayload,
            &DeserializeCalibrateIMUPayload);
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

BCL_STATUS InitializeQueryMicroscopePacket(
        BclPacket *             pkt
)
{
    return InitializeBclPacket(
            pkt,
            QUERY_MICROSCOPE,
            NULL,
            0,
            NULL,
            NULL
    );
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
    if (length < 4 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    ptr = (SoilPayload *)(payload);
    buffer[0] = ptr->temperature >> 8;
    buffer[1] = ptr->temperature & 0xFF;
    buffer[2] = ptr->humidity >> 8;
    buffer[3] = ptr->humidity & 0xFF;

    if (bytes_written)
        *bytes_written = 4 * sizeof(int8_t);

    return BCL_OK;
}

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
    buffer[8] = 0;
    buffer[9] = 0;
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
    const uint16_t* ptr;

    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    if(length < sizeof(uint16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (uint16_t*)payload;
    buffer[0] = (*ptr) >> 8;
    buffer[1] = (*ptr) & 0xFF;

    if(bytes_written)
        (*bytes_written) = sizeof(uint16_t);

    return BCL_OK;
}

BCL_STATUS SerializeByteDisplayPayload(
        const BclPayloadPtr payload,
        uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_written)
{
    //Make sure there is only one byte of data
    if(length != 1)
    {
        return BCL_PAYLOAD_SIZE_MISMATCH;
    }

    //The buffer will just be a string of 8 bits indicating which LED to turn on
    //so, just copy the buffer to the payload
    *buffer = *(uint8_t*)payload;

    if(bytes_written)
        *bytes_written = sizeof(uint8_t);

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
    if (length < 4 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    ptr = (SoilPayload *) payload;
    ptr->temperature = (buffer[0] << 8) | (buffer[1]);
    ptr->humidity = (buffer[2] << 8) | (buffer[3]);

    if (bytes_read)
        *bytes_read = 4 * sizeof(int8_t);

    return BCL_OK;
}

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
    uint16_t* ptr;

    if(!buffer || !payload)
    {
        return BCL_INVALID_PARAMETER;
    }

    //enough size?
    if(length < sizeof(uint16_t))
    {
        return BCL_BUFFER_TOO_SMALL;
    }

    ptr = (uint16_t*) payload;
    (*ptr) = ((buffer[0] << 8) | buffer[1]);

    if(bytes_read)
        (*bytes_read) = sizeof(uint16_t);

    return BCL_OK;
}

BCL_STATUS DeserializeByteDisplayPayload(BclPayloadPtr payload,
        const uint8_t* buffer,
        uint8_t length,
        uint8_t* bytes_read)
{
    //Make sure there is only one byte of data
    if(length != 1)
    {
        return BCL_PAYLOAD_SIZE_MISMATCH;
    }

    //The payload will just be a string of 8 bits indicating which LED to turn on
    //so, just copy the payload to the buffer
    *(uint8_t*)payload = *buffer;

    if(bytes_read)
        *bytes_read = sizeof(uint8_t);

    return BCL_OK;
}

