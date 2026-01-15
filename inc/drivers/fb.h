#ifndef FB_H
#define FB_H
#include <boot/limine.h>

extern struct limine_framebuffer *framebuffer;

void fb_init();

// @param framebuffer - can be any
// @param color - can be in hex (0xRRGGBB)
void fb_plot_pix(uint32_t color, int x, int y);
#endif