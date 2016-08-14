#include "bprintf.h"
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <errno.h>

#define GET_BYTE(val, index) ((char)((val) >> (8 * (index)) & 0xFF))
#define ONE_BYTE_TOKEN      'c'
#define TWO_BYTE_TOKEN      's'
#define FOUR_BYTE_TOKEN     'i'
#define EIGHT_BYTE_TOKEN    'l'

static int validate_fmt_str(const char *fmt);
static int get_fmt_chr_size(char fmt_char);


int bprintf(char *buffer, int size, const char *fmt, Endianness endianness,...)
{
    int required_size;
    int num_args;
    int arg_index;
    int buffer_index;
    const char *itr;
    va_list args;

    if (!buffer || !fmt || size <= 0)
        return -EINVAL;

    /* format specifiers are one char long, hence # args = strlen of fmt */
    num_args = strlen(fmt);
    required_size = validate_fmt_str(fmt);
    if (required_size == 0 || required_size > size)
        return -EINVAL;

    va_start(args, endianness);
    itr = fmt;
    buffer_index = 0;
    arg_index = 0;

    for (itr = fmt; *itr; itr++)
    {
        int fmt_chr_size;
        int i;
        uint64_t val;

    #ifdef _WIN32
        switch (*itr)
        {
            case ONE_BYTE_TOKEN: 
                val = (uint64_t) va_arg(args, uint8_t); 
                break;
            case TWO_BYTE_TOKEN:
                val = (uint64_t) va_arg(args, uint16_t);
                break;
            case FOUR_BYTE_TOKEN: 
                val = (uint64_t) va_arg(args, uint32_t);
                break;
            case EIGHT_BYTE_TOKEN:
                val = (uint64_t) va_arg(args, uint64_t);
                break;
            default:
                va_end(args);
                return -EINVAL;
        }
    #else
        val = (uint64_t) va_arg(args, uint64_t);    
    #endif

        fmt_chr_size = get_fmt_chr_size(*itr);
        if (fmt_chr_size == 0)
        {
            va_end(args);
            return -EINVAL;
        }

        for (i = 0; i < fmt_chr_size; i++)
        {
            if (endianness == Little)
                buffer[buffer_index + i] = GET_BYTE(val, i);
            else
                buffer[buffer_index + i] = GET_BYTE(val, fmt_chr_size - i - 1);
        }

        buffer_index += fmt_chr_size;
        arg_index++;
    }

    va_end(args);

    /* not all arguments consumed! */
    if (arg_index != num_args)
        return -E2BIG;

    return required_size;
}

int bscanf(const char *buffer, int size, const char *fmt, Endianness endianness,...)
{
    int fmt_size;
    int num_args;
    int arg_index;
    va_list args;
    const char *itr;
    int buffer_index;

    if (!buffer || size <= 0 || !fmt)
        return -EINVAL;

    num_args = strlen(fmt);
    fmt_size = validate_fmt_str(fmt);
    if (fmt_size == 0 || fmt_size > size)
        return -EINVAL;

    va_start(args, endianness);

    buffer_index = 0;
    arg_index = 0;
    for (itr = fmt; *itr; itr++)
    {
        char *ptr;
        int size;
        int i;

        size = get_fmt_chr_size(*itr);
        ptr = (char *) va_arg(args, void *);

        for (i = 0; i < size; i++)
        {
            if (endianness == Big)
                ptr[size - i - 1] = buffer[buffer_index + i];
            else
                ptr[size - i - 1] = buffer[buffer_index + size - i - 1];
        }

        buffer_index += size;
        arg_index++; 
    }

    va_end(args);

    /* not all arguments consumed! */
    if (arg_index != num_args)
        return -E2BIG;

    return fmt_size;
}

static int validate_fmt_str(const char *fmt)
{
    int bufsize;
    const char *itr;

    if (!fmt || strlen(fmt) == 0)
        return 0;

    bufsize = 0;
    itr = fmt;

    for (itr = fmt; *itr; itr++)
    {
        int fmt_chr_size;
        fmt_chr_size = get_fmt_chr_size(*itr);

        if (fmt_chr_size == 0)
            return 0;

        bufsize += fmt_chr_size;
    }

    return bufsize;
}

static int get_fmt_chr_size(char fmt_char)
{
    switch (fmt_char)
    {
        case ONE_BYTE_TOKEN: 
            return sizeof(uint8_t);
        case TWO_BYTE_TOKEN: 
            return sizeof(uint16_t);
        case FOUR_BYTE_TOKEN:
             return sizeof(uint32_t);
        case EIGHT_BYTE_TOKEN:
             return sizeof(uint64_t);
        default:
            return 0;
    }
}
