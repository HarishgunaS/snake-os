#include "idt.h"
#include "../drivers/io.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
void set_idt_entry(int index, unsigned long address)
{
    IDT[index].zero = 0;
    IDT[index].selector = 0x08;
    IDT[index].offset_lower = (address & 0xffff);
    IDT[index].offset_higher = (address & 0xffff0000) >> 16;
    IDT[index].type_attr = 0x8e;
}

void initialize_idt(void)
{
    extern int load_idt();
    extern int irq0();
    extern int irq1();
    unsigned long isr0_address = (unsigned long)irq0;
    unsigned long irq1_address = (unsigned long)irq1;
    
    set_idt_entry(32, isr0_address);
    set_idt_entry(33, irq1_address);

    struct IDT_register reg;
    reg.address = (unsigned long)IDT;
    reg.size = sizeof(struct IDT_entry) * 256 - 1;
    

    // initializing both PICs
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    // vector offset
    outb(0x21, 0x20);
    outb(0xA1, 40);

    // tell master that slave at IRQ2, tell slave that it is cascade 2
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    // 8086 mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    // settings masks
    outb(0x21, 0xfc); //set to 0xfd to stop using timer
    outb(0xA1, 0xff);
    load_idt(&reg);

}

void isr0(void)
{
    outb(0x20, 0x20);
    tick();
}

void isr1(void)
{
    outb(0x20, 0x20);
    unsigned char status = inb(0x64);
    if ((status & 0xC3) == 0x01) //checking if there is a time out error or parity error. Also checking if output buffer status is 1 and input buffer status is 0.
    {
        unsigned char input = inb(0x60);
        //do something
        set_key(input);
    }
}