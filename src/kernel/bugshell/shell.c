#include "../../drivers/vga.h"
#include "../kernel.h"
#include <kernel/lib/string.h>
#include <kernel/lib/stdio.h>
char buffer[1024];

void shell_init(){
	kprintf("bugshell 0.1\n");
	memset(buffer, 0, 1024);
}

void sh_mn_loop(){
	memset(buffer, 0, 1024);
	vga_printstr("$ ");
	getstr(buffer, 1024);
	kprintf("\n");
}