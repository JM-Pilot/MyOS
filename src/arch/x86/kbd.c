#include "kbd.h"
#include "irq.h"
#include "asm.h"
#include <stdint.h>
#include "../../drivers/vga.h"
#include <stdbool.h>

char kbdus[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
	0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
char kbdus_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
bool is_shift;
uint8_t last_key;
void kbd_handler(struct registers *r){
	uint8_t scancode;
	scancode = inb(0x60);
	if (scancode == 0x2A || scancode == 0x36) is_shift = true;
    	if (scancode == 0xAA || scancode == 0xB6) is_shift = false;
    	if (scancode & 0x80) {}
	else {
		if (is_shift) {
			last_key = kbdus_shift[scancode];
		} else {
			last_key = kbdus[scancode];
		}
   	}
}
char get_scancode(){
	last_key = 0;
	while (!last_key);
	return last_key;
}

void kbd_install(){
	irq_install_handler(1, kbd_handler);
}
