#if ROBOT == Amelio
#include "MechanicalControlPackets.h"
#include "Packet.h"
#include <string.h>

BCL_STATUS InitializeSetTankDriveSpeedPacket(
	BclPacket *pkt, 
    TankDrivePayload *payload
) {

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
	BclPacket *pkt, 
    AllWheelSpeedPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_ALL_WHEEL_SPEED,
		payload,
		sizeof(AllWheelSpeedPayload),
		&SerializeAllWheelSpeedPayload,
		&DeserializeAllWheelSpeedPayload
	);
}

BCL_STATUS InitializeQueryArmPositionPacket(
	BclPacket *pkt
) {
	return InitializeBclPacket(
		pkt,
		QUERY_ARM_POS,
		NULL,
		0,
		NULL,
		NULL
	);
}

BCL_STATUS InitializeReportArmPositionPacket(
	BclPacket *pkt, 
    ArmPositionPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		REPORT_ARM_POS,
		payload,
		sizeof(ArmPositionPayload),
		&SerializeArmPositionPayload,
		&DeserializeArmPositionPayload
	);
}

BCL_STATUS InitializeSetArmPositionPacket(
	BclPacket *pkt, 
    ArmPositionPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_ARM_POS,
		payload,
		sizeof(ArmPositionPayload),
		&SerializeArmPositionPayload,
		&DeserializeArmPositionPayload
	);
}

BCL_STATUS InitializeSetRideHeightSpeedPacket(
	BclPacket *pkt, 
    RideHeightPayload *payload
) {

	return InitializeBclPacket(
		pkt,
		SET_RIDE_HEIGHT_SPEED,
		payload,
		sizeof(RideHeightPayload),
		&SerializeRideHeightSpeedPayload,
		&DeserializeRideHeightSpeedPayload
	);
}

BCL_STATUS InitializeAllRideHeightSpeedPacket(
	BclPacket *pkt, 
    AllRideHeightSpeedPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_ALL_RIDE_HEIGHT_SPEED,
		payload,
		sizeof(AllRideHeightSpeedPayload),
		&SerializeAllRideHeightSpeedPayload,
		&DeserializeAllRideHeightSpeedPayload
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
	if (bufferLength < 6*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	awsp = (const AllWheelSpeedPayload*)payload;
	buffer[FRONT_LEFT_WHEEL] = awsp->front_left;
	buffer[MIDDLE_LEFT_WHEEL] = awsp->mid_left;
	buffer[BACK_LEFT_WHEEL] = awsp->back_left;
	buffer[FRONT_RIGHT_WHEEL] = awsp->front_right;
	buffer[MIDDLE_RIGHT_WHEEL] = awsp->mid_right;
	buffer[BACK_RIGHT_WHEEL] = awsp->back_right;

	if (bytes_written)
		*bytes_written = sizeof(*awsp);
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

BCL_STATUS  SerializeArmPositionPayload(
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
)
{
    const ArmPositionPayload *app;
    
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
    
    if (length < sizeof(ArmPositionPayload))
        return BCL_BUFFER_TOO_SMALL;
    
    app = (const ArmPositionPayload *)payload;
    
    buffer[TURNTABLE_INDEX] = app->turntable;
    buffer[HUMERUS_INDEX] = app->humerus;
    buffer[FOREARM_INDEX] = app->forearm;
    buffer[WRIST_UP_DOWN_INDEX] = app->wrist_up_down;
    buffer[WRIST_ROT_INDEX] = app->wrist_rot;
    buffer[CLAW_INDEX] = app->claw;
    
    if (bytes_written)
        *bytes_written = 6 * sizeof(int8_t);
    
    return BCL_OK;
}

BCL_STATUS SerializeRideHeightSpeedPayload(
	const BclPayloadPtr     payload,
	uint8_t *               buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_written
)
{
	const RideHeightPayload *rhp;
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < 2*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	rhp = (const RideHeightPayload*)payload;
	buffer[0] = rhp->left;
	buffer[1] = rhp->right;

	if (bytes_written)
		*bytes_written = sizeof(*rhp);
	return BCL_OK;
}

BCL_STATUS SerializeAllRideHeightSpeedPayload(
	const BclPayloadPtr     payload,
	uint8_t *               buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_written
) {
	const AllRideHeightSpeedPayload *arhsp;
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < 4*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	arhsp = (const AllRideHeightSpeedPayload*)payload;
	buffer[FRONT_LEFT_ACTUATOR] = arhsp->front_left;
	buffer[BACK_LEFT_ACTUATOR] = arhsp->back_left;
	buffer[FRONT_RIGHT_ACTUATOR] = arhsp->front_right;
	buffer[BACK_RIGHT_ACTUATOR] = arhsp->back_right;

	if (bytes_written)
		*bytes_written = sizeof(*arhsp);
    return BCL_OK;
}

BCL_STATUS DeserializeAllWheelSpeedPayload(
	BclPayloadPtr     		payload,
	const uint8_t *			buffer,
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
	BclPayloadPtr           payload,
	const uint8_t *			buffer,
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

BCL_STATUS DeserializeArmPositionPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
)
{
    ArmPositionPayload *app;
    
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
    
    if (length < sizeof(ArmPositionPayload))
        return BCL_BUFFER_TOO_SMALL;
    
    app = (ArmPositionPayload *)payload;
    app->turntable = buffer[TURNTABLE_INDEX];
    app->humerus = buffer[HUMERUS_INDEX];
    app->forearm = buffer[FOREARM_INDEX];
    app->wrist_up_down = buffer[WRIST_UP_DOWN_INDEX];
    app->wrist_rot = buffer[WRIST_ROT_INDEX];
    app->claw = buffer[CLAW_INDEX];
    
    if (bytes_read)
        *bytes_read = 6 * sizeof(int8_t);
    
    return BCL_OK;
}

BCL_STATUS DeserializeRideHeightSpeedPayload(
	BclPayloadPtr           payload,
	const uint8_t *			buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_read
	)
{
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < 2*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	RideHeightPayload *rhp;

	rhp = (RideHeightPayload*)(payload);
	rhp->left = buffer[0];
	rhp->right = buffer[1];

	if (bytes_read)
		*bytes_read = 2*sizeof(int8_t);

	return BCL_OK;
}

BCL_STATUS DeserializeAllRideHeightSpeedPayload(
	BclPayloadPtr     		payload,
	const uint8_t *			buffer,
	uint8_t                 bufferLength,
	uint8_t *               bytes_read
)
{
	if (!payload || !buffer)
		return BCL_INVALID_PARAMETER;
	if (bufferLength < sizeof(uint8_t) + 4*sizeof(int8_t))
		return BCL_BUFFER_TOO_SMALL;

	AllRideHeightSpeedPayload *arhsp;

	arhsp = (AllRideHeightSpeedPayload*)(payload);
	arhsp->front_left = buffer[FRONT_LEFT_ACTUATOR];
	arhsp->back_left = buffer[BACK_LEFT_ACTUATOR];
	arhsp->front_right = buffer[FRONT_RIGHT_ACTUATOR];
	arhsp->back_right = buffer[BACK_RIGHT_ACTUATOR];


	if (bytes_read)
		*bytes_read = sizeof(uint8_t) + sizeof(*arhsp);

	return BCL_OK;
}

#endif
