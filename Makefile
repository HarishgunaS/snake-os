C_SOURCES = $(wildcard kernel/*.c interrupts/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h interrupts/*.h drivers/*.h)
OBJS = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
OBJCOPY = /usr/local/i386elfgcc/bin/i386-elf-objcopy
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
QEMU = /usr/bin/qemu-system-i386
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
		 -Wall -Wextra -Werror

%.bin: %.asm
	nasm $< -f bin -o $@

%.o: %.asm
	nasm $< -f elf -o $@

.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

bootloader.bin: boot/boot0.bin boot/boot1.bin
	cat $^ > bootloader.bin


kernel/kernel.elf: boot/load_kernel.o ${OBJS}
	${LD} -o $@ -Ttext 0x2000 $^

kernel/kernel.bin: kernel/kernel.elf
	${OBJCOPY} -O binary $< $@

image.bin: bootloader.bin kernel/kernel.bin
	cat $^ > image.bin

run_vnc: image.bin
	${QEMU} -s -fda $< -vnc :0

run: image.bin
	${QEMU} -s -fda $<

debug: image.bin kernel/kernel.elf
	${QEMU} -s -fda image.bin &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"
clean:
	rm -rf *.bin *.o
	rm -rf kernel/*.o boot/*.bin boot/*.o drivers/*.o interrupts/*.o kernel/*.bin kernel/*.elf