#include "snake.h"
struct Snake* add_block(struct Snake* t)
{
    struct Snake* temp = (struct Snake*)malloc(sizeof(struct Snake));
    temp->x = t->x;
    temp->y = t->y;
    temp->next = t;
    return temp;
}