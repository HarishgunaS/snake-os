#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main()
{

    clear_screen();
    kprint("here i am\n");
    isr_install();
    __asm__ __volatile__("int $4");
    __asm__ __volatile__("int $3");
    kprint("here i am\n");

}