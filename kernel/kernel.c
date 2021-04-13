#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main()
{

    clear_screen();
    isr_install();
    asm volatile("sti");
    init_timer(50);
    init_keyboard();

}