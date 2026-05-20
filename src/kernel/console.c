#include "console.h"
#include "../drivers/video/vgafb.h"
#include "../drivers/video/psf.h"
#include <kernel/lib/string.h>
console_attr_t console_main;

void console_init(){
	console_main.cursor_x = 0;
	console_main.cursor_y = 0;
	console_main.fg = 0xFFFFFF;
	console_main.bg = 0;
}

void printch(char c){
	switch (c){
		case '\n':
			console_main.cursor_x = 0;
			console_main.cursor_y += main_font->height;
			if (console_main.cursor_y >= fb_height)
				console_scrollup();
			return;
		case '\b':
			console_main.cursor_x -= main_font->width;
			psf2_font_render(' ', console_main.cursor_x, console_main.cursor_y,
				console_main.fg, console_main.bg);
			return;
		case '\r':
			console_main.cursor_x = 0;
			return;
		case '\t':
			console_main.cursor_x += (main_font->width * 4);
			return;
	}

	psf2_font_render(c, console_main.cursor_x, console_main.cursor_y,
		console_main.fg, console_main.bg);
	console_main.cursor_x += main_font->width;

	if (console_main.cursor_x >= fb_width){
		console_main.cursor_x = 0;
		console_main.cursor_y += main_font->height;
		if (console_main.cursor_y >= fb_height)
        		console_scrollup();
	}
}
void printstr(const char *s){
	for (int i = 0; s[i] != '\0'; i++)
		printch(s[i]);
}

void printint(int val){
	int i, sign;
	char buffer[10];
	if ((sign = val) < 0){
		val = -val;
	}
	i = 0;
	do {
		buffer[i++] = val % 10 + '0';
	} while ((val /= 10) > 0);

	if (sign < 0){
		buffer[i++] = '-';
	}
	while (i-- > 0)
		printch(buffer[i]);
}

void printhex(uint32_t val) {
	char hex_val[] = "0123456789ABCDEF";
	char buffer[8];
	for (int i = 7; i >= 0; i--) {
		buffer[i] = hex_val[val & 0x0F];
		val >>= 4;
	}
	printstr("0x");
	for (int i = 0; i < 8; i++)
		printch(buffer[i]);
}

void console_scrollup(){
	uint8_t *addr = (uint8_t*)fb_addr;
	uint32_t line = fb_pitch * main_font->height;
	memmove(addr, addr + line, fb_pitch * fb_height - line);
	memset(addr + fb_pitch * fb_height - line, 0, line);
	console_main.cursor_y -= main_font->height;
}