#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

static inline BCL_STATUS SerializeMechanicalControlPacket (const BclPayloadPtr payload,
    										 uint8_t * buffer,
   											 uint8_t length,
    										 uint8_t * bytes_written) {
	*bytes_written = length;
	memcpy (payload, buffer, length);
	
	return BCL_OK;
}

static inline BCL_STATUS DeserializeMechanicalControlPacket ( BclPayloadPtr payload,
    											const uint8_t * buffer,
   												uint8_t length,
    											uint8_t * bytes_read) {
 	*bytes_read = length;
 	memcpy (buffer, payload, length);

	return BCL_OK;

 	
}

BCL_STATUS InitializeWheelSpeedControlPacket(BclPacket *pkt,
											uint8_t numWheels,
											uint8_t *wheelSpeeds) {
	
	uint8_t opcode;
	
	if (numWheels == 2) {
		opcode = WHEELS_SPEED_CTRL_LR; }
		
	if (numWheels == 6) {
		opcode = WHEELS_SPEED_CTRL_INDIV; }
	
	return InitializeBclPacket (
		pkt,
		opcode,
		wheelSpeeds,
		numWheels,
		&SerializeMechanicalControlPacket,
		&DeserializeMechanicalControlPacket);
}

BCL_STATUS InitializeArmPositionControlPacket (
    BclPacket *pkt,
	uint8_t numMotors,
	uint8_t *motorPositions) {
				
	return InitializeBclPacket (
		pkt,
		ARM_POS_CTRL,
		motorPositions,
		numMotors,
		&SerializeMechanicalControlPacket,
		&DeserializeMechanicalControlPacket);
	}
	
	
BCL_STATUS InitializeArmPositionQueryPacket (
	BclPacket *pkt) {
	
	return InitializeBclPacket (
		pkt,
		ARM_POS_QUERY,
		0,
		0,
		&SerializeMechanicalControlPacket,
		&DeserializeMechanicalControlPacket);
	}
	
BCL_STATUS InitializeArmPositionReportPacket (
	BclPacket *pkt,
	uint8_t numMotors,
	uint8_t *motorPositions) {
	
	return InitializeBclPacket (
		pkt,
		ARM_POS_REPORT,
		motorPositions,
		numMotors,
		&SerializeMechanicalControlPacket,
		&DeserializeMechanicalControlPacket);
	}
	
BCL_STATUS InitializeTurretControlPacket (
	BclPacket *pkt,
	uint8_t pan,
	uint8_t tilt) {
	
	uint8_t payload[] = {pan, tilt};
	
	return InitializeBclPacket (
		pkt,
		TURRET_POS_SET,
		payload,
		2,
		&SerializeMechanicalControlPacket,
		&DeserializeMechanicalControlPacket); 
	}
