#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "blocks.h"
#include "colors.h"

// Peripherals constants
#define VGA_CTRL_BASE 0x44A00000

// Borders (frame) constants
#define INT_X_BORDER		1
#define END_X_BORDER		158
#define INT_Y_BORDER		1
#define END_Y_BORDER		108
#define BORDER_THICKNESS	1

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
void print_lives(position_t pos, int lifes);


// ###################################
// ###   CUSTOM GRAPHIC ELEMENTS   ###
// ###################################

// Heart
#define HEART_WIDTH     7
#define HEART_HEIGHT    6
#define HEART_DISTANCE  2
#define LIVES_POS_X     INT_X_BORDER + HEART_DISTANCE
#define LIVES_POS_Y     END_Y_BORDER - HEART_HEIGHT - HEART_DISTANCE

color_t heart[HEART_HEIGHT][HEART_WIDTH] = {
		{H_BL,H_DR,H_DR,H_BL,H_DR,H_DR,H_BL},
		{H_DR,H_MR,H_MR,H_DR,H_MR,H_LR,H_DR},
		{H_DR,H_MR,H_MR,H_MR,H_MR,H_MR,H_DR},
		{H_BL,H_DR,H_MR,H_MR,H_MR,H_DR,H_BL},
		{H_BL,H_BL,H_DR,H_MR,H_DR,H_BL,H_BL},
		{H_BL,H_BL,H_BL,H_DR,H_BL,H_BL,H_BL}
};

// Level selection numbers
color_t number_1[12][9] = {
		{N,N,N,GI,GI,GI,N,N,N},
		{N,N,GI,W,W,GC,GI,N,N},
		{N,GI,W,W,W,GC,GI,N,N},
		{GI,W,W,W,W,GC,GI,N,N},
		{GI,W,W,W,W,GC,GI,N,N},
		{N,GI,GI,W,W,GC,GI,N,N},
		{N,N,GI,W,W,GC,GI,N,N},
		{N,N,GI,W,W,GC,GI,N,N},
		{N,GO,GO,W,W,GC,GO,GO,N},
		{GO,W,W,W,W,W,W,GC,GO},
		{GO,W,W,W,W,W,W,GC,GO},
		{N,GO,GO,GO,GO,GO,GO,N}
};
color_t number_2[12][10] = {
    {N,N,GI,GI,GI,GI,GI,GI,N,N},
	{N,GI,W,W,W,W,W,GC,GI,N},
	{GI,W,W,W,W,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC,GI},
	{N,GI,GI,GI,GI,W,W,W,GC,GI},
	{N,N,N,GI,W,W,W,GC,GI,N},
	{N,N,GI,W,W,W,GC,GI,N,N},
	{N,GO,W,W,W,GC,GO,GO,GO,N},
	{GO,W,W,W,W,W,W,W,GC,GO},
	{GO,W,W,W,W,W,W,W,GC,GO},
	{N,GO,GO,GO,GO,GO,GO,GO,GO,N}

};
color_t number_3[12][9] = {
    {N,N,GI,GI,GI,GI,GI,N,N},
	{N,GI,W,W,W,W,GC,GI,N},
	{GI,W,W,W,W,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC},
	{GI,W,W,GC,GI,GI,W,W,GC},
	{N,GI,GI,GI,W,W,W,GC,GI},
	{N,GI,GI,GI,W,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC},
	{GO,W,W,GC,GO,GO,W,W,GC},
	{GO,W,W,W,W,W,W,GC,GO},
	{N,GO,W,W,W,W,W, GC,GO},
	{N,N,GO,GO,GO,GO,GO,N,N}

};

// Level selection buttons
color_t button[10][9] = {
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GC,GC,GC,GC,N},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GI,GC,GC,GC,GC,GC,GC,GC,GI},
		{GO,GI,GC,GC,GC,GC,GC,GI,GO},
		{N,GO,GI,GI,GI,GI,GI,GO,N},
		{N,N,GO,GO,GO,GO,GO,N,N}
};

// Level selection phrase
color_t choose_level[5][47] = {
		{W,W,W,N,W,N,W,N,W,W,W,N,W,W,W,N,W,W,W,N,W,W,W,N,N,N,W,N,N,N,W,W,W,N,W,N,W,N,W,W,W,N,W,N,N,N,N},
		{W,N,N,N,W,N,W,N,W,N,W,N,W,N,W,N,W,N,N,N,W,N,N,N,N,N,W,N,N,N,W,N,N,N,W,N,W,N,W,N,N,N,W,N,N,N,W},
		{W,N,N,N,W,W,W,N,W,N,W,N,W,N,W,N,W,W,W,N,W,W,N,N,N,N,W,N,N,N,W,W,N,N,W,N,W,N,W,W,N,N,W,N,N,N,N},
		{W,N,N,N,W,N,W,N,W,N,W,N,W,N,W,N,N,N,W,N,W,N,N,N,N,N,W,N,N,N,W,N,N,N,W,N,W,N,W,N,N,N,W,N,N,N,W},
		{W,W,W,N,W,N,W,N,W,W,W,N,W,W,W,N,W,W,W,N,W,W,W,N,N,N,W,W,W,N,W,W,W,N,N,W,N,N,W,W,W,N,W,W,W,N,N}
};

// Level selection authors
color_t authors[14][25] = {
		{M_CYAN,M_CYAN,M_CYAN,N,N,N,M_CYAN,M_CYAN,M_CYAN,N,M_CYAN,N,N,M_CYAN,M_CYAN,M_CYAN,N,M_CYAN,N,M_CYAN,N,N,M_CYAN,M_CYAN,M_CYAN},
		{M_CYAN,N,N,M_CYAN,N,M_CYAN,N,N,M_CYAN,N,N,N,M_CYAN,N,N,M_CYAN,N,M_CYAN,M_CYAN,N,N,M_CYAN,N,N,M_CYAN},
		{M_CYAN,N,N,M_CYAN,N,M_CYAN,N,N,M_CYAN,N,M_CYAN,N,M_CYAN,N,N,M_CYAN,N,M_CYAN,N,N,N,M_CYAN,N,N,M_CYAN},
		{M_CYAN,N,N,M_CYAN,N,N,M_CYAN,M_CYAN,M_CYAN,N,M_CYAN,N,N,M_CYAN,M_CYAN,M_CYAN,N,M_CYAN,N,N,N,N,M_CYAN,M_CYAN,M_CYAN},

		{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N},
		{N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N},
		{N,N,N,N,N,N,N,N,N,N,M_GREEN,N,N,N,N,M_GREEN,N,N,N,N,N,N,N,N,N},
		{N,N,N,N,N,N,N,N,N,N,M_GREEN,N,N,N,N,M_GREEN,N,N,N,N,N,N,N,N,N},
		{M_GREEN,M_GREEN,M_GREEN,N,N,N,M_GREEN,M_GREEN,M_GREEN,N,M_GREEN,M_GREEN,M_GREEN,N,N,M_GREEN,N,N,M_GREEN,M_GREEN,N,N,N,N,N},
		{M_GREEN,N,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,N,N,N},
		{M_GREEN,N,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,M_GREEN,N,M_GREEN,N,N,M_GREEN,N,N,N,N},
		{M_GREEN,M_GREEN,M_GREEN,N,N,N,M_GREEN,M_GREEN,M_GREEN,N,M_GREEN,M_GREEN,M_GREEN,N,N,M_GREEN,N,N,M_GREEN,M_GREEN,N,N,N,N,N},
		{M_GREEN,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N},
		{M_GREEN,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N}
};

// Level selection logo
color_t breakout[7][38] = {
		{W,W,W,N, N, W,W,W,N, N, W,W,W,W, N, W,W,W,W, N, W,N,N,W, N, W,W,W,W, N, W,N,N,W, N, W,W,W},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,W,W,N, N, W,W,W,N, N, W,W,W,N, N, W,W,W,W, N, W,W,N,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,W,N, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,W,W,N, N, W,N,N,W, N, W,W,W,W, N, W,N,N,W, N, W,N,N,W, N, W,W,W,W, N, W,W,W,W, N, N,W,N}
};

// Smoke animation
#define SMOKE_TIME      100000   // microseconds
#define SMOKE_FRAMES    5       // microseconds
#define SMOKE_WIDTH     3       // pixels
#define SMOKE_HEIGHT    6       // pixels

color_t smoke[SMOKE_FRAMES][SMOKE_HEIGHT][SMOKE_WIDTH] = {
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_GC,G_BL},
        {G_BL,G_BL,G_GO},
        {G_BL,G_GC,G_BL},
        {G_GO,G_BL,G_GC}
    },
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_GO,G_BL},
        {G_BL,G_BL,G_GC},
        {G_GC,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    },
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_GO,G_BL,G_BL},
        {G_BL,G_GO,G_GC},
        {G_GC,G_BL,G_GO},
        {G_BL,G_BL,G_BL}
    },
    {
        {G_BL,G_BL,G_GO},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    },
    {
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    }
};

#endif

