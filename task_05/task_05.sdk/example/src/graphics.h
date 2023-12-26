#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "blocks.h"
#include "colors.h"

#define VGA_CTRL_BASE 0x44A00000

// Functions
void paint_object(position_t pos, color_t *object, int height, int width);
void paint_animation(position_t pos, color_t *animation, int frames, int period, int rows, int cols);
void print_background(color_t color);

// Funci�n que pinta un pixel en pantalla
// X entre 0 y 159, Y entre 0 y 119,
// R/G/B: colores - entre 0 y 255 (los cuatro bits menos significativos se ignoran)
void paint(int x, int y, color_t rgb);

// Funci�n que retorna el valor de un pixel en pantalla
color_t pixel(int x, int y);

// Funci�n que pinta un rect�ngulo de un color
// Pos: esquina superior izquierda del rectangulo
// Color: color del rect�ngulo
// W: anchura, H: altura
void rect (position_t pos, color_t col, int w, int h);

#endif

