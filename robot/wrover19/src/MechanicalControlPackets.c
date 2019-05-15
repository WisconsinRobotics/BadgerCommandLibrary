#if ROBOT == WRover19
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
            NULL,
            NULL
    );
}

BCL_STATUS InitializeQueryPidPacket(
    BclPacket *pkt
) {
    return InitializeBclPacket(
        pkt,
        QUERY_PID,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportPidPacket(
    BclPacket *pkt,
    PidPayload *payload
) {
    return InitializeBclPacket(
        pkt,
        REPORT_PID,
        payload,
        sizeof(PidPayload),
        &SerializePidPayload,
        &DeserializePidPayload
    );
}

BCL_STATUS InitializeSetPidPacket(
    BclPacket *pkt,
    PidPayload *payload
) {

    return InitializeBclPacket(
        pkt,
        SET_PID,
        payload,
        sizeof(PidPayload),
        &SerializePidPayload,
        &DeserializePidPayload
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

BCL_STATUS InitializeActivateAugurRotPacket(
    BclPacket *pkt,
    AugurRotationPayload *payload
) {
    return InitializeBclPacket(
        pkt,
        ACTIVATE_AUGUR_ROT,
        payload,
        sizeof(AugurRotationPayload),
        &SerializeAugurRotationPayload,
        &DeserializeAugurRotationPayload
    );
}

BCL_STATUS InitializeActivateAugurLinPacket(
    BclPacket *pkt,
    AugurLinearPayload *payload
) {
    return InitializeBclPacket(
        pkt,
        ACTIVATE_AUGUR_LIN,
        payload,
        sizeof(AugurLinearPayload),
        &SerializeAugurLinearPayload,
        &DeserializeAugurLinearPayload
    );
}

BCL_STATUS InitializeQueryTestTubePacket (
    BclPacket * pkt
) {
    return InitializeBclPacket(
        pkt,
        QUERY_TEST_TUBE_POS,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportTestTubePacket (
    BclPacket * pkt,
    TestTubePayload * payload
) {
    return InitializeBclPacket(
        pkt,
        REPORT_TEST_TUBE_POS,
        payload,
        sizeof(TestTubePayload),
        &SerializeTestTubePayload,
        &DeserializeTestTubePayload
    );
}

BCL_STATUS InitializeSetTestTubePacket(
    BclPacket * pkt,
    TestTubePayload * payload
) {
    return InitializeBclPacket(
        pkt,
        SET_TEST_TUBE_POS,
        payload,
        sizeof(TestTubePayload),
        &SerializeTestTubePayload,
        &DeserializeTestTubePayload
    );
}

BCL_STATUS InitializeQuerySoilCamPacket (
    BclPacket * pkt
) {
    return InitializeBclPacket(
        pkt,
        QUERY_SOIL_CAM_POS,
        NULL,
        0,
        NULL,
        NULL
    );
}

BCL_STATUS InitializeReportSoilCamPacket (
    BclPacket * pkt,
    SoilCamActuatorPayload * payload
)  {
    return InitializeBclPacket(
        pkt,
        REPORT_SOIL_CAM_POS,
        payload,
        sizeof(SoilCamActuatorPayload),
        &SerializeSoilCamActuatorPayload,
        &DeserializeSoilCamActuatorPayload
    );
}

BCL_STATUS InitializeSetSoilCamPacket(
    BclPacket * pkt,
    SoilCamActuatorPayload * payload
)  {
    return InitializeBclPacket(
        pkt,
        SET_SOIL_CAM_POS,
        payload,
        sizeof(SoilCamActuatorPayload),
        &SerializeSoilCamActuatorPayload,
        &DeserializeSoilCamActuatorPayload
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
    
    buffer[TURNTABLE_INDEX] = (uint8_t) 0xFF & ap->turntable;
    buffer[TURNTABLE_INDEX + 1] = (uint8_t) (ap->turntable >> 8);
    buffer[SHOULDER_INDEX] = (uint8_t) 0xFF & ap->shoulder;
    buffer[SHOULDER_INDEX + 1] = (uint8_t) (ap->shoulder >> 8);
    buffer[ELBOW_INDEX] = (uint8_t) 0xFF & ap->elbow;
    buffer[ELBOW_INDEX + 1] = (uint8_t) (ap->elbow >> 8);
    buffer[FOREARM_INDEX] = (uint8_t) 0xFF & ap->forearm;
    buffer[FOREARM_INDEX + 1] = (uint8_t) (ap->forearm >> 8);
    buffer[WRIST_LEFT_INDEX] = (uint8_t) 0xFF & ap->wrist_left;
    buffer[WRIST_LEFT_INDEX + 1] = (uint8_t) (ap->wrist_left >> 8);
    buffer[WRIST_RIGHT_INDEX] = (uint8_t) 0xFF & ap->wrist_right;
    buffer[WRIST_RIGHT_INDEX + 1] = (uint8_t) (ap->wrist_right >> 8);
    buffer[CLAW_INDEX] = (uint8_t) 0xFF & ap->claw;
    buffer[CLAW_INDEX + 1] = (uint8_t) (ap->claw >> 8);
    
    if (bytes_written)
        *bytes_written = 7 * sizeof(int16_t);
    
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

BCL_STATUS SerializePidPayload(
    const BclPayloadPtr     payload,
    uint8_t *               buffer,
    uint8_t                 bufferLength,
    uint8_t *               bytes_written
) {
    const PidPayload *pyld;
    if (!payload || !buffer)
        return BCL_INVALID_PARAMETER;
    if (bufferLength < sizeof(PidPayload))
        return BCL_BUFFER_TOO_SMALL;

    pyld = (const PidPayload*)payload;

    //P
    buffer[0] = (pyld->p >> 24) & 0xFF;
    buffer[1] = (pyld->p >> 16) & 0xFF;
    buffer[2] = (pyld->p >> 8) & 0xFF;
    buffer[3] = (pyld->p) & 0xFF;

    //I
    buffer[4] = (pyld->i >> 24) & 0xFF;
    buffer[5] = (pyld->i >> 16) & 0xFF;
    buffer[6] = (pyld->i >> 8) & 0xFF;
    buffer[7] = (pyld->i) & 0xFF;

    //D
    buffer[8] = (pyld->d >> 24) & 0xFF;
    buffer[9] = (pyld->d >> 16) & 0xFF;
    buffer[10] = (pyld->d >> 8) & 0xFF;
    buffer[11] = (pyld->d) & 0xFF;

    //Addr
    buffer[12] = pyld->addr;

    //vel
    buffer[13] = pyld->vel;

    if (bytes_written)
        *bytes_written = sizeof(*pyld);
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

BCL_STATUS SerializeAugurRotationPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const AugurRotationPayload *arp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(AugurRotationPayload))
        return BCL_BUFFER_TOO_SMALL;

    arp = (const AugurRotationPayload *)payload;
    ((float*)buffer)[0] = arp->velocity;

    if (bytes_written)
        *bytes_written = sizeof(AugurRotationPayload);

    return BCL_OK;
}

BCL_STATUS SerializeAugurLinearPayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const AugurLinearPayload *alp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(AugurLinearPayload))
        return BCL_BUFFER_TOO_SMALL;

    alp = (const AugurLinearPayload *)payload;
    ((float*)buffer)[0] = alp->velocity;

    if (bytes_written)
        *bytes_written = sizeof(AugurLinearPayload);

    return BCL_OK;
}

BCL_STATUS SerializeTestTubePayload(
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const TestTubePayload *ttp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(TestTubePayload))
        return BCL_BUFFER_TOO_SMALL;

    ttp = (const TestTubePayload *)payload;
    ((float*)buffer)[0] = ttp->velocity;

    if (bytes_written)
        *bytes_written = sizeof(TestTubePayload);

    return BCL_OK;
}

BCL_STATUS SerializeSoilCamActuatorPayload (
        const BclPayloadPtr     payload,
        uint8_t *               buffer,
        uint8_t                 length,
        uint8_t *               bytes_written
)
{
    const SoilCamActuatorPayload *scap;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(SoilCamActuatorPayload))
        return BCL_BUFFER_TOO_SMALL;

    scap = (const SoilCamActuatorPayload *)payload;
    ((float*)buffer)[0] = scap->velocity;

    if (bytes_written)
        *bytes_written = sizeof(SoilCamActuatorPayload);

    return BCL_OK;
}

BCL_STATUS DeserializeAllWheelSpeedPayload(
    BclPayloadPtr             payload,
    const uint8_t *            buffer,
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
    const uint8_t *            buffer,
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
    asp->turntable = buffer[TURNTABLE_INDEX] | (buffer[TURNTABLE_INDEX + 1] << 8);
    asp->shoulder = buffer[SHOULDER_INDEX]  | (buffer[SHOULDER_INDEX + 1] << 8);
    asp->elbow = buffer[ELBOW_INDEX] | (buffer[ELBOW_INDEX + 1] << 8);
    asp->forearm = buffer[FOREARM_INDEX] | (buffer[FOREARM_INDEX + 1] << 8);
    asp->wrist_left = buffer[WRIST_LEFT_INDEX] | (buffer[WRIST_LEFT_INDEX + 1] << 8);
    asp->wrist_right = buffer[WRIST_RIGHT_INDEX] | (buffer[WRIST_RIGHT_INDEX + 1] << 8);
    asp->claw = buffer[CLAW_INDEX] | (buffer[CLAW_INDEX + 1] << 8);
    
    if (bytes_read)
        *bytes_read = 7 * sizeof(int16_t);
    
    return BCL_OK;
}

BCL_STATUS DeserializeRideHeightSpeedPayload(
    BclPayloadPtr           payload,
    const uint8_t *            buffer,
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
    BclPayloadPtr             payload,
    const uint8_t *            buffer,
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

BCL_STATUS DeserializePidPayload(
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 bufferLength,
    uint8_t *               bytes_read
)
{
    if (!payload || !buffer)
        return BCL_INVALID_PARAMETER;
    if (bufferLength < sizeof(PidPayload))
        return BCL_BUFFER_TOO_SMALL;

    PidPayload *pyld;

    pyld = (PidPayload*)(payload);

    pyld->p = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    pyld->i = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];
    pyld->d = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];
    pyld->addr = buffer[12];
    pyld->vel = buffer[13];

    if (bytes_read)
        *bytes_read = sizeof(PidPayload);
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

BCL_STATUS DeserializeAugurRotationPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    AugurRotationPayload *arp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(AugurRotationPayload))
        return BCL_BUFFER_TOO_SMALL;

    arp = (AugurRotationPayload *)payload;
    arp->velocity = ((float*)buffer)[0];

    if (bytes_read)
        *bytes_read = sizeof(AugurRotationPayload);

    return BCL_OK;
}

BCL_STATUS DeserializeAugurLinearPayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    AugurLinearPayload *alp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(AugurLinearPayload))
        return BCL_BUFFER_TOO_SMALL;

    alp = (AugurLinearPayload *)payload;
    alp->velocity = ((float*)buffer)[0];

    if (bytes_read)
        *bytes_read = sizeof(AugurLinearPayload);

    return BCL_OK;
}

BCL_STATUS DeserializeTestTubePayload(
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    TestTubePayload *ttp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(TestTubePayload))
        return BCL_BUFFER_TOO_SMALL;

    ttp = (TestTubePayload *)payload;
    ttp->velocity = ((float*)buffer)[0];

    if (bytes_read)
        *bytes_read = sizeof(TestTubePayload);

    return BCL_OK;
}

BCL_STATUS DeserializeSoilCamActuatorPayload (
        BclPayloadPtr           payload,
        const uint8_t *         buffer,
        uint8_t                 length,
        uint8_t *               bytes_read
)
{
    SoilCamActuatorPayload *scap;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < sizeof(SoilCamActuatorPayload))
        return BCL_BUFFER_TOO_SMALL;

    scap = (SoilCamActuatorPayload *)payload;
    scap->velocity = ((float*)buffer)[0];

    if (bytes_read)
        *bytes_read = sizeof(SoilCamActuatorPayload);

    return BCL_OK;
}

#endif
