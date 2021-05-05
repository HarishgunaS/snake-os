C_SOURCES = $(wildcard kernel/*.c)
HEADERS = $(wildcard kernel/*.h)
OBJS = ${C_SOURCES:.c=.o}

%.bin: %.asm
	nasm $< -f bin -o $@

%.o: %.asm
	nasm $< -f elf64 -o $@

%.o: %.c
	gcc -ffreestanding -c $< -o $@

bootloader.bin: boot/boot0.bin boot/boot1.bin
	cat $^ > bootloader.bin

kernel/kernel.bin: boot/load_kernel.o ${OBJS}
	ld -o $@ -Ttext 0x2000 $^ --oformat binary

image.bin: bootloader.bin kernel/kernel.bin
	cat $^ > image.bin

run_vnc: image.bin
	qemu-system-x86_64 -s -fda $< -vnc :0

run: image.bin
	qemu-system-x86_64 -s -fda $<

clean:
	rm -rf *.bin *.o
	rm -rf kernel/*.o boot/*.bin boot/*.o