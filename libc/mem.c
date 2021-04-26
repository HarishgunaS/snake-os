#include "mem.h"

void memory_copy(u8 *source, u8 *destination, int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        *(destination + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len)
{
    u32 i;
    for (i = 0; i < len; i++)
    {
        *(dest + i) = val;
    }
}