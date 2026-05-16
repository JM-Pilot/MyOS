#include <stdint.h>

#ifndef VGA_H
#define VGA_H
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
typedef enum vga_color vga_color_t;

extern uint16_t *vga;
extern uint16_t vga_cursor_x;
extern uint16_t vga_cursor_y;
extern vga_color_t vga_color_fg;
extern vga_color_t vga_color_bg;

void vga_init();
uint8_t vga_mk_color(vga_color_t fg, vga_color_t bg);
uint16_t vga_mk_entry(uint8_t c, uint8_t color);
void vga_mk_entry_at(uint8_t c, uint8_t color, uint8_t x, uint8_t y);
void vga_printch(char c);
void vga_printstr(const char *s);
void vga_printint(int val);
void vga_printhex(uint32_t val);
void vga_scroll_up();
#endif