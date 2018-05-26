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
    ArmPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		REPORT_ARM_POS,
		payload,
		sizeof(ArmPayload),
		&SerializeArmPayload,
		&DeserializeArmPayload
	);
}

BCL_STATUS InitializeSetArmPositionPacket(
	BclPacket *pkt, 
    ArmPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_ARM_POS,
		payload,
		sizeof(ArmPayload),
		&SerializeArmPayload,
		&DeserializeArmPayload
	);
}

BCL_STATUS InitializeQueryArmSpeedPacket(
	BclPacket *pkt
) {
	return InitializeBclPacket(
		pkt,
		QUERY_ARM_SPEED,
		NULL,
		0,
		NULL,
		NULL
	);
}

BCL_STATUS InitializeReportArmSpeedPacket(
	BclPacket *pkt, 
    ArmPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		REPORT_ARM_SPEED,
		payload,
		sizeof(ArmPayload),
		&SerializeArmPayload,
		&DeserializeArmPayload
	);
}

BCL_STATUS InitializeSetArmSpeedPacket(
	BclPacket *pkt, 
    ArmPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_ARM_SPEED,
		payload,
		sizeof(ArmPayload),
		&SerializeArmPayload,
		&DeserializeArmPayload
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

BCL_STATUS InitializeSetCameraMastPacket(
        BclPacket *pkt,
        CameraMastPayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            SET_MAST_POS,
            payload,
            2 * sizeof(int8_t),
            &SerializeCameraMastPayload,
            &DeserializeCameraMastPayload
    );
}

BCL_STATUS InitializeActivateSolenoidPacket(
        BclPacket *pkt,
        SolenoidPayload *payload
)
{
    return InitializeBclPacket(
            pkt,
            ACTIVATE_SOLENOID,
            payload,
            sizeof(SolenoidPayload),
            &SerializeSolenoidPayload,
            &DeserializeSolenoidPayload
    );
}

BCL_STATUS InitializeQuerySoilDoorPacket(
	BclPacket *pkt
) {
	return InitializeBclPacket(
		pkt,
		QUERY_SOIL_DOOR_POS,
		NULL,
		0,
		NULL,
		NULL
	);
}

BCL_STATUS InitializeReportSoilDoorPacket(
	BclPacket *pkt, 
    DynamixelPositionPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		REPORT_SOIL_DOOR_POS,
		payload,
		sizeof(DynamixelPositionPayload),
		&SerializeDynamixelPositionPayload,
		&DeserializeDynamixelPositionPayload
	);
}

BCL_STATUS InitializeSetSoilDoorPacket(
	BclPacket *pkt, 
    DynamixelPositionPayload *payload
) {
	return InitializeBclPacket(
		pkt,
		SET_SOIL_DOOR_POS,
		payload,
		sizeof(DynamixelPositionPayload),
		&SerializeDynamixelPositionPayload,
		&DeserializeDynamixelPositionPayload
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

BCL_STATUS  SerializeArmPayload(
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 length,
    uint8_t *               bytes_written
)
{
    const ArmPayload *ap;
    
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
    
    if (length < sizeof(ArmPayload))
        return BCL_BUFFER_TOO_SMALL;
    
    ap = (const ArmPayload *)payload;
    
    buffer[TURNTABLE_INDEX] = ap->turntable;
    buffer[HUMERUS_INDEX] = ap->humerus;
    buffer[FOREARM_INDEX] = ap->forearm;
    buffer[WRIST_UP_DOWN_INDEX] = ap->wrist_up_down;
    buffer[WRIST_ROT_INDEX] = ap->wrist_rot;
    buffer[CLAW_INDEX] = ap->claw;
    buffer[SLIDING_INDEX] = ap->sliding;
    
    if (bytes_written)
        *bytes_written = 7 * sizeof(int8_t);
    
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
	buffer[0] = rhp->front;
	buffer[1] = rhp->back;

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

BCL_STATUS SerializeCameraMastPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const CameraMastPayload *cmp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    cmp = (const CameraMastPayload *)payload;
    buffer[0] = cmp->pan;
    buffer[1] = cmp->tilt;

    if (bytes_written)
        *bytes_written = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeSolenoidPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const SolenoidPayload *sp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint16_t))
        return BCL_BUFFER_TOO_SMALL;

    sp = (const SolenoidPayload *)payload;
    buffer[0] = sp->duration >> 8;
    buffer[1] = sp->duration;

    if (bytes_written)
        *bytes_written = sizeof(uint16_t);

    return BCL_OK;
}

BCL_STATUS SerializeDynamixelPositionPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const DynamixelPositionPayload *dpp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    dpp = (const DynamixelPositionPayload *)payload;
    buffer[0] = dpp->position;

    if (bytes_written)
        *bytes_written = sizeof(int8_t);

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
	if (bufferLength < sizeof(uint8_t) + 6*sizeof(int8_t))
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

BCL_STATUS DeserializeArmPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
)
{
    ArmPayload *asp;
    
    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;
    
    if (length < sizeof(ArmPayload))
        return BCL_BUFFER_TOO_SMALL;
    
    asp = (ArmPayload *)payload;
    asp->turntable = buffer[TURNTABLE_INDEX];
    asp->humerus = buffer[HUMERUS_INDEX];
    asp->forearm = buffer[FOREARM_INDEX];
    asp->wrist_up_down = buffer[WRIST_UP_DOWN_INDEX];
    asp->wrist_rot = buffer[WRIST_ROT_INDEX];
    asp->claw = buffer[CLAW_INDEX];
    asp->sliding = buffer[SLIDING_INDEX];
    
    if (bytes_read)
        *bytes_read = 7 * sizeof(int8_t);
    
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
	rhp->front = buffer[0];
	rhp->back = buffer[1];

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

BCL_STATUS DeserializeCameraMastPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    CameraMastPayload *cmp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    cmp = (CameraMastPayload *)payload;
    cmp->pan = buffer[0];
    cmp->tilt = buffer[1];

    if (bytes_read)
        *bytes_read = 2 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeSolenoidPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    SolenoidPayload *sp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(uint16_t))
        return BCL_BUFFER_TOO_SMALL;

    sp = (SolenoidPayload *)payload;
    sp->duration = (buffer[0] << 8) | buffer[1];

    if (bytes_read)
        *bytes_read = sizeof(uint16_t);

    return BCL_OK;
}

BCL_STATUS DeserializeDynamixelPositionPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    DynamixelPositionPayload *dpp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    dpp = (DynamixelPositionPayload *)payload;
    dpp->position = buffer[0];

    if (bytes_read)
        *bytes_read = sizeof(int8_t);

    return BCL_OK;
}

#endif
