#ifndef _BCL_STATUS_H
#define _BCL_STATUS_H

typedef enum 
{
    BCL_OK                      = 0,
    BCL_INVALID_PARAMETER       = 1,
    BCL_BUFFER_TOO_SMALL        = 2,
    BCL_OUT_OF_RESOURCES        = 3,
    BCL_NOT_FOUND               = 4,
    BCL_ALREADY_EXISTS          = 5,
    BCL_CHECKSUM_ERROR          = 6,
    BCL_UNSUPPORTED             = 7,
    BCL_SOCKET_ERROR            = 8,
    BCL_SERIAL_ERROR            = 9,
    BCL_GENERIC_ERROR = 255
} BCL_STATUS;

#endif