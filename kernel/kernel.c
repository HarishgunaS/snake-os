#include "../interrupts/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../snake/snake.h"
#define SQUARE_SIZE 10

struct Snake* head;
struct Snake* tail;
// int x = 100;
// int y = 100;
int x_velocity = SQUARE_SIZE;
int y_velocity = 0;


void update_render()
{
    unsigned char input = get_key();
    // square(x, y, SQUARE_SIZE, BLACK);
    if (input == 0x1e)
    {
        //A down
        if (x_velocity == 0)
        {
            x_velocity = -1*SQUARE_SIZE;
            y_velocity = 0;
        }
        
    }
    else if (input == 0x11)
    {
        //W down
        if (y_velocity == 0)
        {
            y_velocity = -1*SQUARE_SIZE;
            x_velocity = 0;
        }
    }
    else if (input == 0x20)
    {
        //D down
        if (x_velocity == 0)
        {
            x_velocity = SQUARE_SIZE;
            y_velocity = 0;
        }
        
    }
    else if (input == 0x1F)
    {
        //S down
        if (y_velocity == 0)
        {
            y_velocity = SQUARE_SIZE;
            x_velocity = 0;
        }
    }


    struct Snake* current = tail;
    square(tail->x, tail->y, SQUARE_SIZE, BLACK);
    while (current->next != 0)
    {
        current->x = current->next->x;
        current->y = current->next->y;
        square(current->x+1, current->y+1, SQUARE_SIZE-2, GREEN);
        current = current->next;
    }
    head->x += x_velocity;
    head->y += y_velocity;
    square(head->x+1, head->y+1, SQUARE_SIZE-2, GREEN);
    
}


int kernel_main()
{
    init_timer();
    init_keyboard();
    initialize_idt();

    struct Snake start;
    start.x = 100;
    start.y = 100;
    start.next = 0;
    struct Snake second;
    second.x = 90;
    second.y = 100;
    second.next = &start;
    struct Snake third;
    third.x = 80;
    third.y = 100;
    third.next = &second;
    struct Snake fourth;
    fourth.x = 80;
    fourth.y = 90;
    fourth.next = &third;
    struct Snake fifth;
    fifth.x = 80;
    fifth.y = 80;
    fifth.next = &fourth;
        
    head = &start;
    tail = &fifth;

    add_function((unsigned long)update_render, 2);

    for(;;)
    {
        asm("hlt");
    }
    return 0;
}
