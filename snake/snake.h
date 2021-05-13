#ifndef SNAKE_H
#define SNAKE_H
#include "../kernel/mem.h"
struct Snake
{
    int x;
    int y;
    struct Snake* next;
};
int appleX;
int appleY;
struct Snake* add_block(struct Snake* t);
struct Snake* head;
struct Snake* tail;
int x_velocity = 10;
int y_velocity = 0;

// void init_snake(int x, int y, int s);

// int size;
// struct Snake* headH;
#endif