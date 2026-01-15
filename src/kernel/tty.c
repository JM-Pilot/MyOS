#include <kernel/tty.h>
#include <stdint.h>
#include <drivers/font.h>
#include <drivers/fb.h>
int curs_x = 0;
int curs_y = 0;
void write_ch(char c, uint32_t color){
	if (curs_x + 9 >= framebuffer->width || c == '\n') {
		curs_x = 0;
		curs_y += 9;
		return;
	}
	if (c == '\t'){
		// 4 tabs
		curs_x += 9 * 4;
		return;
	}
	fnt_draw_char(curs_x, curs_y, c, color);
	curs_x += 9; // 1 pixel gap between characters
}

void write_str(const char *s, uint32_t color){
	for (int i = 0; s[i] != '\0'; i++){
		write_ch(s[i], color);
	}
}