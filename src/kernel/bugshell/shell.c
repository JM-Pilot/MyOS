#include "../console.h"
#include "../../drivers/video/vgafb.h"
#include <kernel/kernel.h>
#include <kernel/lib/string.h>
#include <kernel/lib/stdio.h>
char buffer[1024];

void parse_input(){
	if (strncmp(buffer, "help ", 5) == 0 || 
		strncmp(buffer, "help", 4) == 0){
			kprintf("bugshell by JM-Pilot (KERNEL SHELL)\n");
			kprintf("help     --- Shows list of commands\n");
			kprintf("clear    --- Clears the screen\n");
	}
	if (strncmp(buffer, "clear ", 6) == 0 || 
		strncmp(buffer, "clear", 5) == 0){
			vgafb_clear();
			console_main.cursor_x = 0;
			console_main.cursor_y = 0;
	}
}
void shell_init(){
	kprintf("bugshell 0.1\n");
	memset(buffer, 0, 1024);
}

void sh_mn_loop(){
	memset(buffer, 0, 1024);
	printstr("$ ");
	gets(buffer, 1024);
	kprintf("\n");
	parse_input();
}