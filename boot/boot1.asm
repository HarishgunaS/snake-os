[org 0x1000]
KERNEL_ENTRY equ 0x2000
; establish boot1 exe

mov [DRIVE_NUMBER], dl; storing drive number given by boot0


mov bp, 0x9000; settings base pointer and stack pointer
mov sp, bp

[bits 16]

mov ah, 0x00
mov al, 0x13
int 0x10


;read/load kernel
mov dl, [DRIVE_NUMBER]
mov ah, 0x02
mov al, 30; total sector count
mov ch, 0x00; cylinder & 0xff, cylinder = 0
mov cl, 0x03; sector | ((cylinder >> 2) & 0xC0), cylinder = 0, sector = 2
mov dh, 0x00; head = 0
mov bx, KERNEL_ENTRY; put returned value at BOOT1
int 0x13

mov ah, 0x24; enabling a20 gate
int 0x15


cli; disabling hardware interrupts

lgdt [GDT_DESCRIPTOR];load gdt

mov eax, cr0
or eax, 0x1
mov cr0, eax

jmp CODE_SEG:PROTECTED_MODE; jump to address in code seg to flush cpu pipeline of 16 bit/real mode instructions

[bits 32]

PROTECTED_MODE:
mov ax, DATA_SEG
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

mov ebp, 0x90000
mov esp, ebp

call CODE_SEG:KERNEL_ENTRY

jmp $

GDT_DESCRIPTOR:
    dw GDT_END - GDT_START - 1
    dd GDT_START

GDT_START:
GDT_NULL:
    dd 0x0
    dd 0x0
GDT_CODE:
    dw 0xffff; limit bits 0-15 (max)
    dw 0x0; base bits 0-15, =0
    db 0x0; base bits 16-23, =0
    db 10011010b; present=1, privilege=00, descriptor type=1, code=1, conforming=0, readable=1, accessed=0
    db 11001111b; granularity=1, 32bit default=1, 64bit seg=0, AVL=0, limit bits 16-19 max
    db 0x0; base bits 24-31, =0
GDT_DATA: 
    dw 0xffff; limit bits 0-15 (max)
    dw 0x0; base bits 0-15, =0
    db 0x0; base bits 16-23, =0
    db 10010010b; present=1, privilege=00, descriptor type=1, code=0, expand down=0, writable=1, accessed=0
    db 11001111b; granularity=1, 32bit default=1, 64bit seg=0, AVL=0, limit bits 16-19 max
    db 0x0; base bits 24-31, =0
GDT_END:

CODE_SEG equ GDT_CODE - GDT_START
DATA_SEG equ GDT_DATA - GDT_START

DRIVE_NUMBER:
    db 0

times 510 - ($-$$) db 0
dw 0xaa55