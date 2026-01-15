#ifndef TTY_H
#define TTY_H
#include <stdint.h>

extern int curs_x;
extern int curs_y;
void write_ch(char c, uint32_t color);
void write_str(const char *s, uint32_t color);
#endif