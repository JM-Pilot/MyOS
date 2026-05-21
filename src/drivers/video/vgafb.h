#include <stdint.h>
#include "psf.h"
#include "../../entry/multiboot.h"
#ifndef VGAFB_H
#define VGAFB_H

extern volatile uint32_t *fb_addr;
extern uint32_t fb_width;
extern uint32_t fb_height;
extern uint32_t fb_pitch;

uint32_t vgafb_get_pos(uint32_t x, uint32_t y);
void vgafb_init(struct multiboot_info *mb_i);
void vgafb_plot_pixel(uint32_t col, int x, int y);
void vgafb_clear();
void vgafb_fill(uint32_t col);
#endif