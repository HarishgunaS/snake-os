#include "../interrupts/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../snake/snake.h"
#include "../kernel/mem.h"
#include "../kernel/random.h"



void update_render()
{
    if (dead)
    {
        unsigned char input = get_key();
        if (input == 0x39)
        {
            // free the memory!
            // struct Snake* current = tail;
            // while (current->next != 0)
            // {
            //     struct Snake* temp = current;
            //     current = current->next;

            // }
            init_snake();
            

        }
        return;
    }
        
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
    if (appleX == head->x + x_velocity && appleY == head->y + y_velocity)
    {
        tail = add_block(tail);
        add_apple(randint(MIN_X/SQUARE_SIZE + 10, MAX_X/SQUARE_SIZE - 10)*SQUARE_SIZE, randint(MIN_Y/SQUARE_SIZE, MAX_Y/SQUARE_SIZE)*SQUARE_SIZE);
    }
    square(appleX+1, appleY+1, SQUARE_SIZE-2, RED);
    square(tail->x-1, tail->y-1, SQUARE_SIZE+2, BACKGROUND);
    while (current->next != 0)
    {
        current->x = current->next->x;
        current->y = current->next->y;
        square(current->x+1, current->y+1, SQUARE_SIZE-2, GREEN);
        current = current->next;
    }
    current->x += x_velocity;
    current->y += y_velocity;
    if (get_color(current->x + SQUARE_SIZE/2, current->y + SQUARE_SIZE/2) == GREEN)
    {
        dead = 1;
    }
    square(current->x+1, current->y+1, SQUARE_SIZE-2, GREEN);

    if (x_velocity > 0)
    {
        plot(current->x + 2*SQUARE_SIZE/3, current->y + SQUARE_SIZE/3, BLACK);
        plot(current->x + 2*SQUARE_SIZE/3, current->y + 2*SQUARE_SIZE/3, BLACK);
        // plot(current->x + SQUARE_SIZE, current->y + SQUARE_SIZE/2, LIGHT_RED);
    }
    else if (x_velocity < 0)
    {
        plot(current->x + SQUARE_SIZE/3, current->y + SQUARE_SIZE/3, BLACK);
        plot(current->x + SQUARE_SIZE/3, current->y + 2*SQUARE_SIZE/3, BLACK);
        // plot(current->x, current->y + SQUARE_SIZE/2, LIGHT_RED);
    }
    else if(y_velocity > 0)
    {
        plot(current->x + SQUARE_SIZE/3, current->y + 2*SQUARE_SIZE/3, BLACK);
        plot(current->x + 2*SQUARE_SIZE/3, current->y + 2*SQUARE_SIZE/3, BLACK);
        // plot(current->x + SQUARE_SIZE/2, current->y + SQUARE_SIZE, LIGHT_RED);
    }
    else if (y_velocity < 0)
    {
        plot(current->x + SQUARE_SIZE/3, current->y + SQUARE_SIZE/3, BLACK);
        plot(current->x + 2*SQUARE_SIZE/3, current->y + SQUARE_SIZE/3, BLACK);
        // plot(current->x + SQUARE_SIZE/2, current->y, LIGHT_RED);
    }
    
    
}

int kernel_main()
{
    init_timer();
    init_keyboard();
    initialize_idt();
    init_heap();
    init_snake();
    //new_blocks = rand();

    
    add_function((unsigned long)update_render, 2);

    for(;;)
    {
        asm("hlt");
    }
    return 0;
}
