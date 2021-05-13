#include "screen.h"
void square(int x, int y, int size, unsigned char color)
{
    int i, j;
    for (i = x; i < x + size; i++)
    {
        for (j = y; j < y + size; j++)
        {
            plot(i, j, color);
        }
    }
}
void plot(int x, int y, unsigned char color)
{
    if (x >= MAX_X || y >= MAX_Y || x < MIN_X || y < MIN_Y)
    {
        return; //throw error?
    }
    unsigned short offset;
    offset = 320*y + x;    
    unsigned char *pixel = (unsigned char*)0xA0000;
    pixel[offset] = color;
}

unsigned char get_color(int x, int y)
{
    if (x >= MAX_X || y >= MAX_Y || x < MIN_X || y < MIN_Y)
    {
        return GREEN; //throw error?
    }
    unsigned short offset;
    offset = 320*y + x;    
    unsigned char *pixel = (unsigned char*)0xA0000;
    return pixel[offset];
}

void clear_screen(unsigned char color)
{
    int i, j;
    for (i = MIN_X; i < MAX_X; i++)
    {
        for (j = MIN_Y; j < MAX_Y; j++)
        {
            plot(i, j, color);
        }
    }
}
