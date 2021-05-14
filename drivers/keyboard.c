#include "keyboard.h"
#include "screen.h"
void init_keyboard()
{
    key = 0x00;
    end = 0;
    current = 0;
}
void set_key(unsigned char k)
{
    key = k;
    key_buffer[end++] = k;
}

unsigned char get_key()
{
    unsigned char val = 0x00;
    if (current < end)
    {
        val = key_buffer[current++];
    }
    if (current == end)
    {
        end = 0;
        current = 0;
    }
    return val;
}