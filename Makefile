CC = x86_64-elf-gcc
AS = x86_64-elf-as
NASM = nasm -f elf64
SRC = src
INC = inc
BIN = bin
C_SRCS := $(wildcard $(SRC)/kernel/*.c) \
	$(wildcard $(SRC)/drivers/*.c) \
	$(wildcard $(SRC)/boot/*.c) \
	$(wildcard $(SRC)/x86_64/*.c) 

ASM_SRCS := $(wildcard $(SRC)/x86_64/*.s)
NASM_SRCS := $(wildcard $(SRC)/x86_64/*.asm)

C_OBJS := $(addprefix $(BIN)/,$(notdir $(patsubst %.c,%.o,$(C_SRCS))))
ASM_OBJS := $(addprefix $(BIN)/,$(notdir $(patsubst %.s,%.o,$(ASM_SRCS))))
NASM_OBJS := $(addprefix $(BIN)/,$(notdir $(patsubst %.asm,%.o,$(NASM_SRCS))))

OBJS = $(C_OBJS) $(ASM_OBJS) $(NASM_OBJS)

OUTPUT = MyOS
CFLAGS = -ffreestanding \
	-nostdlib \
	-Wall -Wextra \
	-I$(INC) \
	-m64 \
	-mno-red-zone \
	-mcmodel=kernel
LDFLAGS = -ffreestanding \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	-T $(SRC)/boot/linker.ld

.PHONY: all iso run clean

all: $(BIN)/$(OUTPUT).iso

$(BIN)/$(OUTPUT).bin: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(BIN)/%.o: $(SRC)/kernel/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/drivers/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/boot/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/x86_64/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/x86_64/%.s | $(BIN)
	$(AS) $< -o $@

$(BIN)/%.o: $(SRC)/x86_64/%.asm | $(BIN)
	$(NASM) $< -o $@

$(BIN)/$(OUTPUT).iso: $(BIN)/$(OUTPUT).bin
	rm -f $@
	cp $(BIN)/$(OUTPUT).bin boot/MyOS.bin
	xorriso -as mkisofs -R -r -J -b limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		boot -o $@
	limine bios-install $@

$(BIN):
	mkdir -p $@

run: $(BIN)/$(OUTPUT).iso
	qemu-system-x86_64 -cdrom $(BIN)/$(OUTPUT).iso -d int -D QEMU_LOG.txt -no-reboot -no-shutdown

clean:
	rm -rf $(BIN)