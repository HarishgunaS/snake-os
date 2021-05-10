#include "../interrupts/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"



int kernel_main()
{
    init_timer();
    init_keyboard();
    initialize_idt();
    
    int x = 100;
    int y = 100;
    int x_velocity = 1;
    int y_velocity = 0;


    while (1)
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
        sleep_ms(1);
    }
    // while (1)
    // {
    //     
    
    // }
    for(;;)
    {
        asm("hlt");
    }
    return 0;
}
