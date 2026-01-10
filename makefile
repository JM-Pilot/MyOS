SRC = src
BIN = bin

CC = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -ffreestanding -nostdlib -O2 -Wall -Wextra -Iinc
LDFLAGS = -ffreestanding -nostdlib -O2 -lgcc

all: compile iso run

OFILES = ${BIN}/boot.o ${BIN}/kernel.o ${BIN}/vga.o
compile:
	mkdir -p bin
	${AS} ${SRC}/boot.s -o ${BIN}/boot.o
	${CC} -c ${SRC}/kernel.c -o ${BIN}/kernel.o ${CFLAGS}
	${CC} -c ${SRC}/vga.c -o ${BIN}/vga.o ${CFLAGS}

	${CC} -T ${SRC}/linker.ld ${OFILES} -o ${BIN}/MyOS.bin ${LDFLAGS}
iso:
	cp ${BIN}/MyOS.bin isodir/boot/MyOS.bin
	cp ${SRC}/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ${BIN}/MyOS.iso isodir
run:
	qemu-system-i386 -cdrom ${BIN}/MyOS.iso
