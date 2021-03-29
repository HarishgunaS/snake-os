all: run

kernel.bin: kernel_entry.o kernel.o

kernel_entry.o: kernel_entry.asm

kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

boot.bin: boot.asm
	nasm $< -f bin -o $@

os-image.bin: boot.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -fda $<

clean:
	rm *.bin *.o *.dis