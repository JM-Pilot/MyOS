#include <stdint.h>
#include <vga.h>
#include <port_io.h>
void kernel_main(){
	vga_init();
	print_str("TEST MESSAGE! :)");
	for (;;);
}
