#ifndef _BCL_STATUS_H
#define _BCL_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    /** The operation succeeded. */
    BCL_OK                      = 0,

    /** An invalid parameter (e.g. NULL) was supplied. */
    BCL_INVALID_PARAMETER,

    /** The buffer supplied is too small for the requested operation. */
    BCL_BUFFER_TOO_SMALL,

    /**  Failed to allocate the resource necessary for the operation. */
    BCL_OUT_OF_RESOURCES,

    /** The requested resource was not found. */
    BCL_NOT_FOUND,

    /** This operation is unsupported for this platform. */
    BCL_UNSUPPORTED,

    /** The packet's start bytes did not match the expected start bytes. */
    BCL_BAD_PACKET_START,

    /** The packet's end byte did not match the expected end byte. */
    BCL_BAD_PACKET_END,

    /** The packet's opcode did not match the expected opcode. */
    BCL_OPCODE_MISMATCH,

    /** The packet's destination robot ID does not match this robot's ID. */
    BCL_ROBOT_ID_MISMATCH,

    /** The packet's payload size does not match the expected message payload size. */
    BCL_PAYLOAD_SIZE_MISMATCH,

    /** The received packet is not a complete packet. */
    BCL_CLIPPED_PACKET,

    /** The payload checksum does not match the provided checksum. */
    BCL_CHECKSUM_ERROR,

    /** A socket error has occurred. */
    BCL_SOCKET_ERROR,

    /** A serial port error has occurred. */
    BCL_SERIAL_ERROR,

    /** A generic error has occurred. */
    BCL_GENERIC_ERROR = 255
} BCL_STATUS;

#ifdef __cplusplus
}
#endif

#endif