SRC = src
BIN = bin

CC = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -ffreestanding -nostdlib -O2 -Wall -Wextra -Iinc
LDFLAGS = -ffreestanding -nostdlib -O2 -lgcc

all: compile iso run

OFILES = $(wildcard bin/*.o)
compile:
	mkdir -p bin
	${AS} ${SRC}/x86/boot.s -o ${BIN}/boot.o
	${CC} -c ${SRC}/kernel.c -o ${BIN}/kernel.o ${CFLAGS}
	${CC} -c ${SRC}/vga.c -o ${BIN}/vga.o ${CFLAGS}
	${CC} -c ${SRC}/port_io.c -o ${BIN}/port_io.o ${CFLAGS}

	${CC} -c ${SRC}/x86/gdt.c -o ${BIN}/gdt_c.o ${CFLAGS}
	${AS} ${SRC}/x86/gdt.s -o ${BIN}/gdt_s.o

	${CC} -c ${SRC}/x86/idt.c -o ${BIN}/idt_c.o ${CFLAGS}
	nasm -felf32 ${SRC}/x86/idt.s -o ${BIN}/idt_s.o
	${CC} -T ${SRC}/x86/linker.ld ${OFILES} -o ${BIN}/MyOS.bin ${LDFLAGS}
iso:
	cp ${BIN}/MyOS.bin isodir/boot/MyOS.bin
	grub-mkrescue -o ${BIN}/MyOS.iso isodir
run:
	qemu-system-i386 -cdrom ${BIN}/MyOS.iso -no-shutdown -no-reboot -serial stdio -d int
clean:
	rm -rf bin/*