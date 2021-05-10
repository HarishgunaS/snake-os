#include "keyboard.h"
#include "screen.h"
void init_keyboard()
{
    key = 0x00;
}
void set_key(unsigned char k)
{
    key = k;
}

unsigned char get_key()
{
    return key;
}