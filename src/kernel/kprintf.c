#include <stdarg.h>
#include <stdint.h>
#include "console.h"

void kprintf(const char *str, ...){
	va_list args;
	va_start(args, str);
	while (*str){
		if (*str == '%'){
			str++;
			switch (*str) {
				case 'c':
					printch((char)va_arg(args, int));
					break;
				case 's':
					printstr(va_arg(args, const char*));
					break;
				case 'd':
					printint(va_arg(args, int));
					break;
				case 'x':
					printhex(va_arg(args, uint32_t));
					break;
				case '%':
					printch('%');
					break;
				default:
					printch('c');
					printch(*str);
					break;
			}
		} else {
			printch(*str);
		}
		str++;
	}
	va_end(args);
}