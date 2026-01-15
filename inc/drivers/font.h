// FONTS ARE NOT MINE
// SOURCE:
/*
 * 8x8 monochrome bitmap fonts for rendering
 * Author: Daniel Hepper <daniel@hepper.net>
 *
 * License: Public Domain
 *
 * Based on:
 * // Summary: font8x8.h
 * // 8x8 monochrome bitmap fonts for rendering
 * //
 * // Author:
 * //     Marcel Sondaar
 * //     International Business Machines (public domain VGA fonts)
 * //
 * // License:
 * //     Public Domain
 *
 * Fetched from: http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm
 */
#ifndef FONT_H
#define FONT_H
#include <stdint.h>
extern uint32_t FONT[128][8];
// but this is mine
void fnt_draw_char(int x, int y, char c, uint32_t color);
#endif