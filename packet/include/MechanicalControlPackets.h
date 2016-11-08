#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

#define WHEELS_SET_LR_SPDS    0x60
#define WHEELS_SET_INDIV_SPDS 0x61
#define ARM_SET_POS           0x62
#define ARM_REPORT_POS        0x63
#define ARM_QUERY_POS         0x68
#define CAMERA_SET_POS        0x64

#ifdef __cplusplus
extern "C" {
#endif

BCL_STATUS InitializeWheelSpeedControlPacket (
    BclPacket *pkt,
	uint8_t numWheels,
	uint8_t *wheelSpeeds
);

BCL_STATUS InitializeArmPositionControlPacket (
    BclPacket *pkt,
	uint8_t numMotors,
	uint8_t *motorPositions
);

BCL_STATUS InitializeArmPositionQueryPacket (
	BclPacket *pkt
);

BCL_STATUS InitializeArmPositionReportPacket (
	BclPacket *pkt,
	uint8_t numMotors,
	uint8_t *motorPositions
);

BCL_STATUS InitializeCameraControlPacket (
	BclPacket *pkt,
	uint8_t pan,
	uint8_t tilt
);

#ifdef __cplusplus
}
#endif

#endif