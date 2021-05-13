#ifndef SNAKE_H
#define SNAKE_H
#include "../kernel/mem.h"
#define SQUARE_SIZE 10

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
int x_velocity;
int y_velocity;
void init_snake();
void add_apple();
int dead;
// void init_snake(int x, int y, int s);

// int size;
// struct Snake* headH;
#endif