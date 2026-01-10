#include <stdint.h>
#include <vga.h>
#include <port_io.h>
#include <x86/gdt.h>
void kernel_main(){
	vga_init();
	gdt_init();
	print_str("TEST MESSAGE! :)");
	for (;;);
}
