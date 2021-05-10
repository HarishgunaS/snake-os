
#include "../interrupts/idt.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
int kernel_main()
{
    init_timer();
    init_keyboard();
    initialize_idt();
    
    int x = 0;
    while (1)
    {
        sleep_ms(1);
        clear_screen(BLACK);
        square(x++, 10, 5, RED);
    }
    // while (1)
    // {
    //     unsigned char input = get_key();
    //     if (input == 0x1e)
    //     {
    //         //A down
            
    //         clear_screen(RED);
    //     }
    //     else if (input == 0x9e)
    //     {
    //         //A up
    //         clear_screen(BLACK);
    //     }
    //     else if (input == 0x11)
    //     {
    //         //W down
    //         clear_screen(GREEN);

    //     }
    //     else if (input == 0x91)
    //     {
    //         //W up
    //         clear_screen(BLACK);
    //     }
    //     else if (input == 0x20)
    //     {
    //         //D down
    //         clear_screen(RED);
    //     }
    //     else if (input == 0xA0)
    //     {
    //         //D up
    //         clear_screen(BLACK);
    //     }
    //     else if (input == 0x1F)
    //     {
    //         //S down
    //         clear_screen(GREEN);
    //     }
    //     else if (input == 0x9f)
    //     {
    //         //S up
    //         clear_screen(BLACK);
    //     }
    // }
    for(;;)
    {
        asm("hlt");
    }
    return 0;
}
