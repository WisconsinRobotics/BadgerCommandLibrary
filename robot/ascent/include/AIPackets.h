#if ROBOT == Ascent
#ifndef _AI_PACKETS_H
#define _AI_PACKETS_H

#include "AscentCommon.h"
#include "BclStatus.h"
#include "Packet.h"

#ifdef __cplusplus
extern "C" {
#endif

/* enum definitions */
typedef enum AI_STATUS
{
    /* 0-50: General Updates */
    AIS_FOUND_GATE = 0,
    AIS_ACK = 1,
    AIS_LOG = 2,

    /* 51-100: State change/status update */
    AIS_SWITCH_VISION = 51,
    AIS_SWITCH_GPS = 52,
    AIS_OBS_DETECT = 53,
    AIS_OBS_AVOID = 54,
	AIS_IN_WATCHDOG = 55,
	AIS_OUT_WATCHDOG = 56,

    /* 101-150: GPS codes */
    AIS_DIST_FROM_GOAL = 101,

    /* 151-200: Vision codes */
    AIS_BALL_DETECT = 151, 
    AIS_DIST_DETECT_BALL = 152,
    AIS_BEGAN_SCAN = 153,
    AIS_DROP_BALL = 154,

    AIS_VERIFY_SUCCESS = 170,
    AIS_VERIFY_FAIL_TIMESTAMP = 171,
    AIS_VERIFY_FAIL_CAM_AVG = 172,
    AIS_VERIFY_FAIL_CAM_PERCENT = 173,
    AIS_VERIFY_FAIL_GPS_AVG = 174,
    AIS_VERIFY_FAIL_GPS_PERCENT = 175,


    /* 201-255: Error codes */
    AIS_FATAL_ERROR = 201,
    AIS_CONN_LOST = 202,
    AIS_CAM_ERR = 203
} AI_STATUS;

/* Payload definitions */
typedef struct AISimplePayload
{
    uint8_t status;
    uint8_t data[8];
} AISimplePayload;

typedef struct AIDebugPayload
{
    uint8_t status;
    char log[150];
} AIDebugPayload;

/* Initialization function definitions */

BCL_STATUS InitializeAISimpleInfoPacket (
    BclPacket *             pkt,
    AISimplePayload *       payload
);

BCL_STATUS InitializeAIDebugInfoPacket (
    BclPacket *             pkt,
    AIDebugPayload *        payload
);

/* Serialization function definitions */

BCL_STATUS SerializeAISimpleInfoPayload (
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

BCL_STATUS SerializeAIDebugInfoPayload(
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
);

/* Deserialization function definitions */

BCL_STATUS DeserializeAISimpleInfoPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);

BCL_STATUS DeserializeAIDebugInfoPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
);


#ifdef __cplusplus
}
#endif
#endif
#endif