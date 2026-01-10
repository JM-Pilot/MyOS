#include <vga.h>
#include <port_io.h>
uint16_t* VGA;
uint16_t cursor_x;
uint16_t cursor_y;

uint16_t make_attr(uint8_t fg, uint8_t bg){
	return ((bg << 4) | (fg & 0x0F) << 8);
}

void vga_init(){
	cursor_x = 0;
	cursor_y = 0;
	VGA = (uint16_t*)0xB8000;
	print_str("VGA Initialized\n");
}

void print_ch(char c){
	if (cursor_x >= VGA_Width){
		cursor_x = 0;
		cursor_y++;
	}
	if (c == '\n'){
		cursor_x = 0;
		cursor_y++;
		return;
	}
	VGA[cursor_y * VGA_Width + cursor_x++] = c | make_attr(0x0F, 0x00);
	move_curs(cursor_x, cursor_y);
}

void print_str(const char* s){
	for (int i = 0; s[i] != '\0'; i++){
		print_ch(s[i]);
	}
}

void disable_curs(){
	out_port(0x3D4, 0x0A);
	out_port(0X3D5, 0x20);
}

void enable_curs(uint8_t cursor_start, uint8_t cursor_end){
	out_port(0x3D4, 0x0A);
	out_port(0x3D5, (in_port(0x3D5) & 0xC0) | cursor_start);

	out_port(0x3D4, 0x0B);
	out_port(0x3D5, (in_port(0x3D5) & 0xE0) | cursor_end);
}

void move_curs(int x, int y){
	uint16_t pos = y * VGA_Width + x;
	out_port(0x3D4, 0x0F);
	out_port(0x3D5, (uint8_t) (pos & 0xFF));
	out_port(0x3D4, 0x0E);
	out_port(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}