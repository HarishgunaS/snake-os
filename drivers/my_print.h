#include "../cpu/ports.h"

void my_print(char* string, int length)
{
    port_byte_out(0x3d4, 14);
    int position = port_byte_in(0x3d5);
    position = position << 8;
    port_byte_out(0x3d4, 15);
    position += port_byte_in(0x3d5);
    
    char *vga = (char*)0xb8000;
    int i;
    for (i = 0; i < length; i++)
    {
        int offset_from_vga = (position + i) * 2;
    
        
        vga[offset_from_vga] = string[i];
        vga[offset_from_vga+1] = 0x0f;
    }
    
}