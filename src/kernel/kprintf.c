#include <stdarg.h>
#include <stdint.h>
#include "../drivers/vga.h"

void kprintf(const char *str, ...){
	va_list args;
	va_start(args, str);
	while (*str){
		if (*str == '%'){
			str++;
			switch (*str) {
				case 'c':
					vga_printch((char)va_arg(args, int));
					break;
				case 's':
					vga_printstr(va_arg(args, const char*));
					break;
				case 'd':
					vga_printint(va_arg(args, int));
					break;
				case 'x':
					vga_printhex(va_arg(args, uint32_t));
					break;
				case '%':
					vga_printch('%');
					break;
				default:
					vga_printch('c');
					vga_printch(*str);
					break;
			}
		} else {
			vga_printch(*str);
		}
		str++;
	}
	va_end(args);
}