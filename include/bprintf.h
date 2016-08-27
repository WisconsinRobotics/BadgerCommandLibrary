#ifndef _BPRINTF_H
#define _BPRINTF_H

typedef enum
{
    Big, 
    Little
} Endianness;

int bprintf(
    void *buffer,
    int size, 
    const char *fmt, 
    Endianness endianness,
    ...
);

int bscanf(
    const void *buffer,
    int size,
    const char *fmt,
    Endianness endianness,
    ...
);


#endif
