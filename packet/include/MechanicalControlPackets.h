#ifndef _MECHANICAL_CONTROL_PACKETS_H
#define _MECHANICAL_CONTROL_PACKETS_H

#include "BclStatus.h"
#include "Packet.h"

#define WHEELS_SPEED_CTRL_LR    0x60
#define WHEELS_SPEED_CTRL_INDIV 0x61
#define ARM_POS_CTRL            0x62
#define ARM_POS_REPORT          0x63
#define ARM_POS_QUERY           0x68
#define TURRET_POS_SET          0x64

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

BCL_STATUS InitializeTurretControlPacket (
	BclPacket *pkt,
	uint8_t pan,
	uint8_t tilt
);

#ifdef __cplusplus
}
#endif

#endif