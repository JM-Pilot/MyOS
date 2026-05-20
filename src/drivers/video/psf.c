#include <stdint.h>
#include "psf.h"
#include "vgafb.h"
extern char _binary_src_misc_cp850_8x16_psfu_start;
psf2_font_t *main_font;

int psf2_font_load(){
	main_font = (psf2_font_t *)&_binary_src_misc_cp850_8x16_psfu_start;
	if (main_font->magic != PSF2_MAGIC)
		return 1;
	return 0;
}
void psf2_font_render(uint8_t c, int x, int y, uint32_t fg, uint32_t bg){
	uint8_t *glyph = (uint8_t*)&_binary_src_misc_cp850_8x16_psfu_start +
		main_font->header_size + (c && c < main_font ->glyph_cnt ? c:0)*main_font->bytes_per_glyph;
	
	for (uint32_t fy = 0; fy < main_font->height; fy++){
		uint8_t byte = glyph[fy];
		for (uint32_t fx = 0; fx < main_font->width; fx++){
			if ((byte & (0x80 >> fx))){
				vgafb_plot_pixel(fg, x + fx, y + fy);
			} else {
				vgafb_plot_pixel(bg, x + fx, y + fy);
			}
		}
	}
}