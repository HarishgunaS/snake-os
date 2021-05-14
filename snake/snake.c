#include "snake.h"
struct Snake* add_block(struct Snake* t)
{
    struct Snake* temp = (struct Snake*)malloc(sizeof(struct Snake));
    temp->x = t->x;
    temp->y = t->y;
    temp->next = t;
    return temp;
}
void init_snake()
{
    x_velocity = 0;
    y_velocity = 0;
    dead = 0;

    srand(get_ticks());
    struct Snake* start = malloc(sizeof(struct Snake));
    start->x = randint(MIN_X/SQUARE_SIZE + 10, MAX_X/SQUARE_SIZE - 10)*SQUARE_SIZE;
    start->y = randint(MIN_Y/SQUARE_SIZE + 10, MAX_Y/SQUARE_SIZE - 10)*SQUARE_SIZE;
    start->next = 0;
    head = start;
    tail = head;
    clear_screen(BACKGROUND);
    add_apple(randint(MIN_X/SQUARE_SIZE + 10, MAX_X/SQUARE_SIZE - 10)*SQUARE_SIZE, randint(MIN_Y/SQUARE_SIZE, MAX_Y/SQUARE_SIZE)*SQUARE_SIZE);
}

void add_apple(int x, int y)
{
    appleX = x;
    appleY = y;
}