#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#define VGA_Width 80
#define VGA_Height 25
extern uint16_t* VGA;
extern uint16_t cursor_x;
extern uint16_t cursor_y;

uint16_t make_attr(uint8_t fg, uint8_t bg);
void vga_init();
void print_ch(char c);
void print_str(const char *s);
void disable_curs();
void enable_curs(uint8_t cursor_start, uint8_t cursor_end);
void move_curs(int x, int y);
#endif