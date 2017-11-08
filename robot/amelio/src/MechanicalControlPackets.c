#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

BCL_STATUS InitializeSetTankDriveSpeedPacket(
	BclPacket *pkt, TankDrivePayload *payload) {

	return InitializeBclPacket(
		pkt,
		SET_TANK_DRIVE_SPEED,
		payload,
		sizeof(TankDrivePayload),
		&SerializeTankDriveSpeedPayload,
		&DeserializeTankDriveSpeedPayload
	);
}

BCL_STATUS InitializeAllWheelSpeedPacket(
	BclPacket *pkt, AllWheelSpeedPayload *payload) {
	return InitializeBclPacket(
		pkt,
		SET_ALL_WHEEL_SPEED,
		payload,
		sizeof(AllWheelSpeedPayload),
		&SerializeAllWheelSpeedPayload,
		&DeserializeAllWheelSpeedPayload
	);
}

BCL_STATUS SerializeAllWheelSpeedPayload(
	const BclPayloadPtr     payload,
	uint8_t *               buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_written
) {
	const AllWheelSpeedPayload *awsp;
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < sizeof(uint8_t) + 6*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	awsp = (const AllWheelSpeedPayload*)payload;
	buffer[FRONT_LEFT_WHEEL] = awsp->front_left;
	buffer[MIDDLE_LEFT_WHEEL] = awsp->mid_left;
	buffer[BACK_LEFT_WHEEL] = awsp->back_left;
	buffer[FRONT_RIGHT_WHEEL] = awsp->front_right;
	buffer[MIDDLE_RIGHT_WHEEL] = awsp->mid_right;
	buffer[BACK_RIGHT_WHEEL] = awsp->back_right;

	if (bytes_written)
		*bytes_written = sizeof(uint8_t) + sizeof(*awsp);
	return BCL_OK;
}

BCL_STATUS SerializeTankDriveSpeedPayload(
	const BclPayloadPtr     payload,
	uint8_t *               buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_written
)
{
	const TankDrivePayload *tdp;
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < 2*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	tdp = (const TankDrivePayload*)payload;
	buffer[0] = tdp->left;
	buffer[1] = tdp->right;

	if (bytes_written)
		*bytes_written = sizeof(*tdp);
	return BCL_OK;
}


BCL_STATUS DeserializeAllWheelSpeedPayload(
	const BclPayloadPtr     payload,
	uint8_t *				buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_read
)
{
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < sizeof(uint8_t) + 6*sizeof(int8_t))//why???????? WILLLLLLL!
		return BCL_BUFFER_TOO_SMALL;

	AllWheelSpeedPayload *awsp;

	awsp = (AllWheelSpeedPayload*)(payload);
	awsp->front_left = buffer[FRONT_LEFT_WHEEL];
	awsp->mid_left = buffer[MIDDLE_LEFT_WHEEL];
	awsp->back_left = buffer[BACK_LEFT_WHEEL];
	awsp->front_right = buffer[FRONT_RIGHT_WHEEL];
	awsp->mid_right = buffer[MIDDLE_RIGHT_WHEEL];
	awsp->back_right = buffer[BACK_RIGHT_WHEEL];


	if (bytes_read)
		*bytes_read = sizeof(uint8_t) + sizeof(*awsp);

	return BCL_OK;
}





BCL_STATUS DeserializeTankDriveSpeedPayload(
	const BclPayloadPtr           payload,
	uint8_t *				  buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_read
	)
{
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < 2*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	TankDrivePayload *tdp;

	tdp = (TankDrivePayload*)(payload);
	tdp->left = buffer[0];
	tdp->right = buffer[1];

	if (bytes_read)
		*bytes_read = 2*sizeof(int8_t);

	return BCL_OK;
}