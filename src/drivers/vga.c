#include "vga.h"
#include <stdint.h>
uint16_t *vga = (uint16_t*)0xB8000;
uint16_t vga_cursor_x;
uint16_t vga_cursor_y;
vga_color_t vga_color_fg;
vga_color_t vga_color_bg;

uint32_t get_vga_cell_pos(uint8_t x, uint8_t y){
	return y * VGA_WIDTH + x;
}
void vga_init(){
	vga_cursor_x = 0;
	vga_cursor_y = 0;
	vga_color_fg = VGA_COLOR_WHITE;
	vga_color_bg = VGA_COLOR_BLACK;
}
uint8_t vga_mk_color(vga_color_t fg, vga_color_t bg){
	return (fg | bg << 4);
}
uint16_t vga_mk_entry(uint8_t c, uint8_t color){
	return c | (color << 8);
}

void vga_mk_entry_at(uint8_t c, uint8_t color, uint8_t x, uint8_t y){
	vga[get_vga_cell_pos(x, y)] = vga_mk_entry(c, color);
}
void vga_printch(char c){
	switch (c){
		case '\n':
			vga_cursor_x = 0;
			vga_cursor_y++;
			if (vga_cursor_y >= VGA_HEIGHT){
				vga_cursor_y = 0;
			}
			return;
		case '\r':
			vga_cursor_x = 0;
			return;	
		case '\b':
			if (vga_cursor_x == 0) return;
			vga_cursor_x--;
			return;
		case '\t':
			if (vga_cursor_x + 4 >= VGA_WIDTH && vga_cursor_y < VGA_HEIGHT){
				vga_cursor_x = 0;
				vga_cursor_y++;
			}
			vga_cursor_x += 4;
			return;
	}
	vga[get_vga_cell_pos(vga_cursor_x++, vga_cursor_y)] = 
	vga_mk_entry(c, vga_mk_color(vga_color_fg, vga_color_bg));
	if (vga_cursor_x >= VGA_WIDTH){
		vga_cursor_x = 0;
		vga_cursor_y++;
	}
	if (vga_cursor_y >= VGA_HEIGHT){
		vga_cursor_x = 0;
		vga_cursor_y = 0;
	}
}
void vga_printstr(const char *s){
	for (int i = 0; s[i] != '\0'; i++)
		vga_printch(s[i]);
}
void vga_printint(int val){
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
		vga_printch(buffer[i]);
}

void vga_printhex(uint32_t val) {
	char hex_val[] = "0123456789ABCDEF";
	char buffer[8];
	for (int i = 7; i >= 0; i--) {
		buffer[i] = hex_val[val & 0x0F];
		val >>= 4;
	}
	vga_printstr("0x");
	for (int i = 0; i < 8; i++)
		vga_printch(buffer[i]);
}