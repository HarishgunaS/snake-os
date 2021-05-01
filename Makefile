bootsector:
	nasm -fbin boot/boot0.asm -o boot/boot.bin

run_vnc: bootsector
	qemu-system-x86_64 -s -fda boot/boot.bin -vnc :0
