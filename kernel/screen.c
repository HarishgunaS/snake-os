void square(int x, int y, int size, unsigned char color)
{
    for (int i = x; i < x + size; i++)
    {
        for (int j = y; j < y + size; j++)
        {
            plot(i, j, color);
        }
    }
}
void plot(int x, int y, unsigned char color)
{
    unsigned short offset;
    offset = 320*y + x;    
    unsigned char *pixel = (unsigned char*)0xA0000;
    pixel[offset] = color;
}
