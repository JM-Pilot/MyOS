#include "kbd.h"
#include "irq.h"
#include "asm.h"
#include <stdint.h>
#include "../../drivers/vga.h"
char kbdus[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
	0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void kbd_handler(struct registers *r){
	uint8_t scancode;
	scancode = inb(0x60);
    	if (scancode & 0x80) {}
	else {
       		vga_printch(kbdus[scancode]);
   	}
}
void kbd_install(){
	irq_install_handler(1, kbd_handler);
}
