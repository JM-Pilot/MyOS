#include <stdint.h>
#include "vgafb.h"
#include "psf.h"
#include "../../entry/multiboot.h"
#include <kernel/lib/string.h>
volatile uint32_t *fb_addr;
uint32_t fb_width;
uint32_t fb_height;
uint32_t fb_pitch;

uint32_t vgafb_get_pos(uint32_t x, uint32_t y){
	return y * (fb_pitch / 4) + x;
}

void vgafb_init(struct multiboot_info *mb_i){
	fb_addr = (volatile uint32_t*)(uintptr_t)mb_i->framebuffer_addr;
	fb_width = mb_i->framebuffer_width;
	fb_height = mb_i->framebuffer_height;
	fb_pitch = mb_i->framebuffer_pitch;

	psf2_font_load(&main_font);
}

void vgafb_plot_pixel(uint32_t col, int x, int y){
	fb_addr[vgafb_get_pos(x, y)] = col;
}

void vgafb_clear(){
	uint8_t *addr = (uint8_t*)fb_addr;
	memset(addr, 0, fb_pitch * fb_height);
}
