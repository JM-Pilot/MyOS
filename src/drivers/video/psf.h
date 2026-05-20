#include <stdint.h>
#ifndef PSF_H
#define PSF_H

#define PSF2_MAGIC 0x864AB572
typedef struct psf2_font {
	uint32_t magic;
	uint32_t version;
	uint32_t header_size;
	uint32_t flags;
	uint32_t glyph_cnt;
	uint32_t bytes_per_glyph;
	uint32_t height;
	uint32_t width;
} psf2_font_t;

extern psf2_font_t *main_font;
int psf2_font_load();
void psf2_font_render(uint8_t c, int x, int y, uint32_t fg, uint32_t bg);
#endif