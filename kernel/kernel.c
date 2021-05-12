#include "../interrupts/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"

int red = 1;

int x = 100;
int y = 100;
int x_velocity = 1;
int y_velocity = 0;

void update_render()
{
    unsigned char input = get_key();
    square(x, y, 5, BLACK);
    if (input == 0x1e)
    {
        //A down
        if (x_velocity == 0)
        {
            x_velocity = -1;
            y_velocity = 0;
        }
        
    }
    else if (input == 0x11)
    {
        //W down
        if (y_velocity == 0)
        {
            y_velocity = -1;
            x_velocity = 0;
        }
    }
    else if (input == 0x20)
    {
        //D down
        if (x_velocity == 0)
        {
            x_velocity = 1;
            y_velocity = 0;
        }
        
    }
    else if (input == 0x1F)
    {
        //S down
        if (y_velocity == 0)
        {
            y_velocity = 1;
            x_velocity = 0;
        }
    }
    
    x += x_velocity;
    y += y_velocity;

    square(x, y, 5, RED);
}


int kernel_main()
{
    init_timer();
    init_keyboard();
    initialize_idt();
    add_function((unsigned long)update_render, 1);

    for(;;)
    {
        asm("hlt");
    }
    return 0;
}
