#include <stdint.h>
#include <vga.h>
void kernel_main(){
	vga_init();
	print_str("Hello World");
	for (;;);
}
