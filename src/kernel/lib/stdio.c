#include <kernel/lib/stdio.h>
#include <stdint.h>
#include "../../arch/x86/kbd.h"
#include "../../drivers/vga.h"
char getch(){
	char ch = get_scancode();
	return ch;
}

char* gets(char *buffer, uint32_t size){
	uint32_t i = 0;
	char c;
	while ((c = getch()) != '\n' && i < size){
		if (c == '\b') {
			if (i > 0)
				i--;
			else
				continue;
		} else {
			buffer[i++] = c;
		}
		vga_printch(c);
	}
	return buffer;
}