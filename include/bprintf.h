#ifndef _BPRINTF_H
#define _BPRINTF_H

typedef enum
{
    Big, 
    Little
} Endianness;

int bprintf(
    char *buffer,
    int size, 
    const char *fmt, 
    Endianness endianness,
    ...
);

int bscanf(
    const char *buffer,
    int size,
    const char *fmt,
    Endianness endianness,
    ...
);


#endif
