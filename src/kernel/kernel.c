#include <boot/limine_requests.h>
#include <kernel/panic.h>
#include <drivers/fb.h>
#include <x86_64/gdt.h>
#include <x86_64/idt.h>
void kernel_main(){
	load_gdt();
	idt_init();
	fb_init();
	for (int i = 0; i < 255; i++){
		fb_plot_pix(0xFF0000, i * (framebuffer->pitch / 4) + i, 0);
	}
	for (;;);
}