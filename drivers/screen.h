#ifndef SCREEN_H
#define SCREEN_H

#define GREEN 0x02
#define RED 0x04
#define BLACK 0x00
#define MIN_X 1
#define MAX_X 321 //exclusive
#define MIN_Y 0
#define MAX_Y 200 //exclusive

void plot(int x, int y, unsigned char color);
void square(int x, int y, int size, unsigned char color);
void clear(unsigned char color);
#endif