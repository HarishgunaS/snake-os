# Snake OS
A baremetal x86 "operating system" that only runs the popular game Snake.

Inspired by https://github.com/jdah/tetris-os

## Running/Testing:
### Requirements:
* qemu-system-i386
* nasm
* Cross compilation: GCC and binutils for i386-elf (gdb, gcc, ld, objcopy)
### Instructions:
```bash
git clone https://github.com/HarishgunaS/snake-os.git
```
Replace the paths found in the Makefile with the correct paths for the installed tools listed above.
```bash
make run
```




## Completed:
* Basic two stage bootloader (no multiboot support)
    * loads Global Descriptor Table
    * enters 32 bit protected mode
    * launches kernel
* Basic interrupt setup
    * Creates and loads simple IDT, masks proper IRQs in PIC
    * Basic ISRs for IRQ0 and IRQ1 (timer and keyboard interrupts)
* Naive preliminary device drivers
    * Keyboard driver (returns last keyboard input)
    * Timer driver (returns ticks since kernel launch, can sleep for given ticks)
    * Screen driver (drawing mode set using BIOS interrupts during boot, can draw pixels and squares at given coordinates using VGA memory)
* Snake gameplay
    * Basic moving square on screen controlled by WASD


## Resources:
* most learning and general information from wiki.osdev.org
* bootloader instructions from http://www.cs.cmu.edu/~410-s07/p4/p4-boot.pdf
* prior knowledge from os-tutorial by cfenollosa
