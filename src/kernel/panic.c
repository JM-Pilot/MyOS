#include <kernel/kernel.h>
#include "../drivers/video/vgafb.h"
#include "console.h"
void panic(const char *msg){
	vgafb_clear();
	vgafb_fill(0x0000FF);
	console_main.cursor_x = 0;
	console_main.cursor_y = 0;
	console_main.fg = 0xFF0000;
	console_main.bg = 0x0000FF;
	kprintf("PANIC!!\n");
	kprintf("MSG: %s\n", msg);
	kprintf("\n\n\nREBOOT YOUR COMPUTER NOW");
	hcf();
}