#include "mem.h"
void init_heap()
{
    
    base_address = (void*)(0x0001);
    current_address = base_address;
    max_address = (void*)(0x2000);
}

void* malloc(int size)
{
    if (current_address >= max_address)
    {
        return 0;
    }
    void* toReturn = current_address;
    current_address += size;
    int i;
    for (i = 0; i < size; i++)
    {
        *(unsigned char*)(toReturn + i) = 0x00;
    }
    return toReturn;
}