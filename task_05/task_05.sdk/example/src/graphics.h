#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "blocks.h"
#include "colors.h"

// Peripherals constants
#define VGA_CTRL_BASE       0x44A00000

// Borders (frame) constants
#define INT_X_BORDER		1
#define END_X_BORDER		158
#define INT_Y_BORDER		1
#define END_Y_BORDER		108
#define BORDER_THICKNESS	1

// Heart
#define HEART_WIDTH         7
#define HEART_HEIGHT        6
#define HEART_DISTANCE      2
#define LIVES_POS_X         HEART_DISTANCE
#define LIVES_POS_Y         RESOLUTION_Y - HEART_HEIGHT - HEART_DISTANCE

// Numbers
#define NUMBERS_WIDTH	    3
#define NUMBERS_HEIGHT	    5

// Blocks
#define BLOCKS_WIDTH	    24
#define BLOCKS_HEIGHT	    5
#define BLOCKS_DISTANCE     2
#define BLOCKS_POS_X	    RESOLUTION_X - (NUMBERS_WIDTH * 4) - BLOCKS_WIDTH + 1
#define BLOCKS_POS_Y	    RESOLUTION_Y - BLOCKS_HEIGHT - BLOCKS_DISTANCE

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
void print_frame();
void print_lives(int lives, int max_lives, color_t *heart);
void print_blocks_info(int left_blocks, color_t *blocks, color_t *numbers);

#endif