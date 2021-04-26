#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memory_copy(u8 *source, u8 *destination, int num);
void memory_set(u8 *dest, u8 val, u32 len);

#endif
