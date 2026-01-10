#include <stdint.h>

#define VGA_Width 80
#define VGA_Height 25
uint16_t* VGA;
uint16_t cursor_x;
uint16_t cursor_y;


uint16_t make_attr(uint8_t fg, uint8_t bg){
	return (bg << 4) | (fg & 0x0F);
}
void vga_init(){
	cursor_x = 0;
	cursor_y = 0;
	VGA = (uint16_t*)0xB8000;
}
void print_ch(char c){
	if (cursor_x >= VGA_Width){
		cursor_x = 0;
		cursor_y++;
	}
	VGA[cursor_y * VGA_Width + cursor_x++] = c | (make_attr(0x0F, 0x00) << 8);
}

void kernel_main(){
	vga_init();
	for (;;);
}
