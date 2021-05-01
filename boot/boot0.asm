[org 0x7c00]
BOOT1 equ 0x1000

cli; disabling hardware interrupts

mov [DRIVE_NUMBER], dl; storing drive number given by bios

mov bp, 0x9000; settings base pointer and stack pointer
mov sp, bp

sti; enable hardware interrupts

[bits 16]

mov ah, 0; reset floppy disk controller
int 0x13

mov dl, [DRIVE_NUMBER]
mov ah, 0x02
mov al, 15; total sector count
mov ch, 0x00; cylinder & 0xff, cylinder = 0
mov cl, 0x02; sector | ((cylinder >> 2) & 0xC0), cylinder = 0, sector = 2
mov dh, 0x00; head = 0
mov bx, BOOT1; put returned value at BOOT1
int 0x13

; call BOOT1

;add error checks!!!!!!!!!1

jmp $
DRIVE_NUMBER:
    db 0

times 510 - ($-$$) db 0
dw 0xaa55