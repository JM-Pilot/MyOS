#include <stdint.h>
#ifndef CONSOLE_H
#define CONSOLE_H

typedef struct console_attr {
	uint32_t cursor_x;
	uint32_t cursor_y;
	uint32_t fg;
	uint32_t bg;
} console_attr_t;

extern console_attr_t console_main;
void console_init();
void printch(char c);
void printstr(const char *s);
void printint(int val);
void printhex(uint32_t val);
void console_scrollup();
#endif