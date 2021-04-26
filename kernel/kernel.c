#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "kernel.h"

void main()
{

    clear_screen();
    isr_install();
    irq_install();

}

void user_input(char *input)
{
    if (strcmp(input, "END") == 0)
    {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    kprint("You said:");
    kprint(input);
    kprint("\n>");
}