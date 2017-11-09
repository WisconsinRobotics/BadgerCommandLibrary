#if ROBOT == Ascent
#include "AIPackets.h"
#include <string.h>

BCL_STATUS InitializeAISimpleInfoPacket (
        BclPacket *                 pkt, 
        AISimplePayload *           payload
)
{
    return InitializeBclPacket (
            pkt,
        AI_SIMPLE_REPORT,
            payload,
            9 * sizeof(uint8_t),
            &SerializeAISimpleInfoPayload,
            &DeserializeAISimpleInfoPayload
    );
}

BCL_STATUS InitializeAIDebugInfoPacket (
            BclPacket *             pkt, 
            AIDebugPayload *        payload
)
{
    return InitializeBclPacket (
        pkt,
        AI_DEBUG_REPORT,
        payload,
        1 * sizeof(uint8_t) + 150 * sizeof(char),
        &SerializeAIDebugInfoPayload,
        &DeserializeAIDebugInfoPayload
    );
}

BCL_STATUS SerializeAISimpleInfoPayload (
    const BclPayloadPtr         payload, 
    uint8_t *                   buffer, 
    uint8_t                     length, 
    uint8_t *                   bytes_written
)
{
    const AISimplePayload *aisp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    // enough size?
    if (length < 9 * sizeof(uint8_t))
        return BCL_BUFFER_TOO_SMALL;

    aisp = (const AISimplePayload *)(payload);
    buffer[0] = aisp->status;
    memcpy(buffer + 1, aisp->data, 8 * sizeof(uint8_t));

    if (bytes_written)
        *bytes_written = 9 * sizeof(int8_t);

    return BCL_OK;
}

BCL_STATUS SerializeAIDebugInfoPayload (
    const BclPayloadPtr         payload,
    uint8_t *                   buffer,
    uint8_t                     length,
    uint8_t *                   bytes_written
)
{
    const AIDebugPayload *aidp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    // enough size?
    if (length < 1 * sizeof(uint8_t) + 150 * sizeof(char))
        return BCL_BUFFER_TOO_SMALL;

    aidp = (const AIDebugPayload *)(payload);
    buffer[0] = aidp->status;
    memcpy(buffer + 1, aidp->log, 150 * sizeof(char));

    if (bytes_written)
        *bytes_written = 1 * sizeof(int8_t) + 150 * sizeof(char);

    return BCL_OK;
}

BCL_STATUS DeserializeAISimpleInfoPayload (
    BclPayloadPtr           payload, 
    const uint8_t *         buffer, 
    uint8_t                 length, 
    uint8_t *               bytes_read
)
{
    AISimplePayload *aisp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    aisp = (AISimplePayload *)payload;
    aisp->status = buffer[0];
    memcpy(aisp->data, buffer + 1, 8 * sizeof(uint8_t));

    if (bytes_read)
        *bytes_read = 9 * sizeof(uint8_t);

    return BCL_OK;
}

BCL_STATUS DeserializeAIDebugInfoPayload (
    BclPayloadPtr           payload,
    const uint8_t *         buffer,
    uint8_t                 length,
    uint8_t *               bytes_read
)
{
    AIDebugPayload *aidp;

    if (!buffer || !payload)
        return BCL_INVALID_PARAMETER;

    if (length < 2 * sizeof(int8_t))
        return BCL_BUFFER_TOO_SMALL;

    aidp = (AIDebugPayload *)payload;
    aidp->status = buffer[0];
    memcpy(aidp->log, buffer + 1, 150 * sizeof(char));

    if (bytes_read)
        *bytes_read = 1 * sizeof(uint8_t) + 150 * sizeof(char);

    return BCL_OK;
}
#endif