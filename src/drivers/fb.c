#include <boot/limine.h>
#include <drivers/fb.h>
#include <boot/limine_requests.h>
#include <kernel/panic.h>

struct limine_framebuffer *framebuffer;
void fb_init(){
	if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
		cpu_haltf();
	}
	framebuffer = framebuffer_request.response->framebuffers[0];
}

void fb_plot_pix(uint32_t color, int x, int y){
	volatile uint32_t *fb_ptr = framebuffer->address;
	fb_ptr[y * framebuffer->width + x] = color;
}