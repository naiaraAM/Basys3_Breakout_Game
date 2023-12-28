#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "blocks.h"
#include "colors.h"

#define VGA_CTRL_BASE 0x44A00000

// ################################
// ###   FUNCTION DEFINITIONS   ###
// ################################

// Generic functions
void paint_object(position_t pos, color_t *object, int height, int width);
void paint_animation(position_t pos, color_t *animation, int frames, int period, int rows, int cols);
void print_background(color_t color);
void paint(int x, int y, color_t rgb);
color_t get_color(int x, int y);
void rect(position_t pos, color_t col, int w, int h);

// Custom graphic element functions
#define HEART_WIDTH 7
#define HEART_HEIGHT 6
#define HEART_DISTANCE 2
void print_lives(position_t pos, int lifes);


// ###################################
// ###   CUSTOM GRAPHIC ELEMENTS   ###
// ###################################

color_t heart[HEART_HEIGHT][HEART_WIDTH] = {
		{H_BL,H_DR,H_DR,H_BL,H_DR,H_DR,H_BL},
		{H_DR,H_MR,H_MR,H_DR,H_MR,H_LR,H_DR},
		{H_DR,H_MR,H_MR,H_MR,H_MR,H_MR,H_DR},
		{H_BL,H_DR,H_MR,H_MR,H_MR,H_DR,H_BL},
		{H_BL,H_BL,H_DR,H_MR,H_DR,H_BL,H_BL},
		{H_BL,H_BL,H_BL,H_DR,H_BL,H_BL,H_BL}
};

#endif

