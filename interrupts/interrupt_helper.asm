global load_idt
global irq0
global irq1

extern isr0
extern isr1


load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

irq0:
    cli
    pusha
    call isr0
    popa
    sti
    iret

irq1:
    cli
    pusha
    call isr1
    popa
    sti
    iret