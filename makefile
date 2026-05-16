OUTPUT = MyOS
CC = i686-elf-gcc
AS = i686-elf-as

SRC_DIR = src
BIN_DIR = bin
INC_DIR = inc

C_FLAGS = -ffreestanding \
	  -march=i686 \
	  -I$(INC_DIR) \
	  -nostdlib \
	  -std=gnu11 \
	  -Wall \
	  -Wextra \
	  -c

LD_FLAGS = -ffreestanding \
	   -nostdlib \
	   -T src/entry/linker.ld

C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/$(SRC_DIR)/%.c.o, $(shell find $(SRC_DIR) -iname "*.c"))
AS_OBJS = $(patsubst $(SRC_DIR)/%.s, $(BIN_DIR)/$(SRC_DIR)/%.s.o, $(shell find $(SRC_DIR) -iname "*.s"))
OBJS = $(C_OBJS) $(AS_OBJS)

$(BIN_DIR)/$(SRC_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $< -o $@

$(BIN_DIR)/$(SRC_DIR)/%.s.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

$(BIN_DIR)/$(OUTPUT).bin: $(OBJS)
	$(CC) $(LD_FLAGS) $^ -o $@
	if grub-file --is-x86-multiboot $@; then \
		echo [LOG] MULTIBOOT CONFIRMED; \
	else \
		echo [LOG] MULTIBOOT NOT CONFIRMED; \
		exit 1; \
	fi;

$(BIN_DIR)/$(OUTPUT).iso: $(BIN_DIR)/$(OUTPUT).bin
	mkdir -p $(BIN_DIR)/iso_build/boot/grub
	cp $(SRC_DIR)/entry/grub.cfg $(BIN_DIR)/iso_build/boot/grub/
	cp $< $(BIN_DIR)/iso_build/boot
	grub-mkrescue -o $@ $(BIN_DIR)/iso_build

run: $(BIN_DIR)/$(OUTPUT).iso
	qemu-system-i386 -hda $< -no-reboot -no-shutdown -d int,cpu_reset -D $(BIN_DIR)/QEMU_LOG.txt

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $@