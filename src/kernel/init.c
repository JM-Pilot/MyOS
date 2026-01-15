#include <kernel/tty.h>
#include <boot/limine_requests.h>
#include <kernel/panic.h>
#include <drivers/fb.h>
#include <x86_64/gdt.h>
#include <x86_64/idt.h>
#include <kernel/tty.h>
void init_all(){
	fb_init();
	write_str("FRAMEBUFFER INITIALIZED!\n", 0x00FF00);
	
	write_str("INITIALIZING GDT -- ", 0xFFFFFF);
	load_gdt();
	write_str(" GOOD\n", 0x00FF00);

	write_str("INITIALIZING IDT -- ", 0xFFFFFF);
	idt_init();
	write_str(" GOOD\n", 0x00FF00);

	write_str("INIT COMPLETE\n", 0x00FF00);
}