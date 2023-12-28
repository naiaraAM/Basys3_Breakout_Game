#ifndef __MAIN_H__
#define __MAIN_H__

#include "blocks.h"
#include "colors.h"
#include "graphics.h"
#include "timer.h"
#include "leds.h"


typedef struct ball {
	int x, y, mov;
} ball_t;

typedef enum side {top, bottom, right, left,
					top_left, top_right, bottom_left, bottom_right,
					not_border} side_t;

typedef enum movement {mov_top_right, mov_bottom_right, mov_bottom_left, mov_top_left} movement_t;

typedef enum game_status {continues, lost_life, block_broken, win, game_over} game_status_t;

// Device constants
#define MAX_LED 		0x8000
#define BASE_GPIO0 		0x40000000
#define BASE_GPIO1 		0x40010000
#define MASK_BUTTONS	0xF

// Bar specification constants
#define BAR_LENGTH			13
#define BAR_HEIGHT			2
#define BAR_SPEED			1

// Ball specification constants
#define BALL_SPEED			3

// Game parameters
#define NUM_LIVES			3
#define NUM_LED_LAPS		3

// Function definitions
void move_bar(int dir, position_t *bar_pos);
void init_ball(ball_t *ball, position_t *bar_pos);
game_status_t move_ball(ball_t *ball, position_t *bar_pos);
void init_buttons();
int check_button();
void wait_button();
side_t calculate_border(position_t next_pos);
bool calculate_block(position_t next_pos, block_t **block);
movement_t calculate_rebound(ball_t *ball, side_t side, bool is_block, block_t block, position_t *next_pos, position_t *bar_pos);
side_t which_side_bar(position_t next_pos, position_t *bar_pos);
levels_t level_selection();
void life_lost(int lives, ball_t *ball, position_t *bar_pos);
void reset_bar_position(position_t *bar_pos);
void game_win();


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

// Level selection numbers
color_t number_1_level[12][9] = {
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
color_t number_2_level[12][10] = {
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
color_t number_3_level[12][9] = {
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
color_t button_left[10][9] = {
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GC,GC,GC,GC,N},
		{GC,GC,GC,GO,GC,GC,GC,GC,GC},
		{GC,GC,GO,GO,GC,GC,GC,GC,GC},
		{GC,GO,GO,GO,GO,GC,GO,GC,GC},
		{GC,GC,GO,GO,GC,GC,GC,GC,GC},
		{GI,GC,GC,GO,GC,GC,GC,GC,GI},
		{GO,GI,GC,GC,GC,GC,GC,GI,GO},
		{N,GO,GI,GI,GI,GI,GI,GO,N},
		{N,N,GO,GO,GO,GO,GO,N,N}
};
color_t button_left_pressed[10][9] = {
		{N,N,N,N,N,N,N,N,N},
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GC,GC,GC,GC,N},
		{GC,GC,GC,GO,GC,GC,GC,GC,GC},
		{GC,GC,GO,GO,GC,GC,GC,GC,GC},
		{GC,GO,GO,GO,GO,GC,GO,GC,GC},
		{GC,GC,GO,GO,GC,GC,GC,GC,GC},
		{GI,GC,GC,GO,GC,GC,GC,GC,GI},
		{N,GI,GC,GC,GC,GC,GC,GI,N},
		{N,N,GI,GI,GI,GI,GI,N,N}
};
color_t button_top[10][9] = {
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GO,GC,GC,GC,N},
		{GC,GC,GC,GO,GO,GO,GC,GC,GC},
		{GC,GC,GO,GO,GO,GO,GO,GC,GC},
		{GC,GC,GC,GC,GO,GC,GC,GC,GC},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GI,GC,GC,GC,GO,GC,GC,GC,GI},
		{GO,GI,GC,GC,GC,GC,GC,GI,GO},
		{N,GO,GI,GI,GI,GI,GI,GO,N},
		{N,N,GO,GO,GO,GO,GO,N,N}
};
color_t button_top_pressed[10][9] = {
		{N,N,N,N,N,N,N,N,N},
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GO,GC,GC,GC,N},
		{GC,GC,GC,GO,GO,GO,GC,GC,GC},
		{GC,GC,GO,GO,GO,GO,GO,GC,GC},
		{GC,GC,GC,GC,GO,GC,GC,GC,GC},
		{GC,GC,GC,GC,GC,GC,GC,GC,GC},
		{GI,GC,GC,GC,GO,GC,GC,GC,GI},
		{N,GI,GC,GC,GC,GC,GC,GI,N},
		{N,N,GI,GI,GI,GI,GI,N,N}
};
color_t button_right[10][9] = {
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GC,GC,GC,GC,N},
		{GC,GC,GC,GC,GC,GO,GC,GC,GC},
		{GC,GC,GC,GC,GC,GO,GO,GC,GC},
		{GC,GC,GO,GC,GO,GO,GO,GO,GC},
		{GC,GC,GC,GC,GC,GO,GO,GC,GC},
		{GI,GC,GC,GC,GC,GO,GC,GC,GI},
		{GO,GI,GC,GC,GC,GC,GC,GI,GO},
		{N,GO,GI,GI,GI,GI,GI,GO,N},
		{N,N,GO,GO,GO,GO,GO,N,N}
};
color_t button_right_pressed[10][9] = {
		{N,N,N,N,N,N,N,N,N},
		{N,N,GC,GC,GC,GC,GC,N,N},
		{N,GC,GC,GC,GC,GC,GC,GC,N},
		{GC,GC,GC,GC,GC,GO,GC,GC,GC},
		{GC,GC,GC,GC,GC,GO,GO,GC,GC},
		{GC,GC,GO,GC,GO,GO,GO,GO,GC},
		{GC,GC,GC,GC,GC,GO,GO,GC,GC},
		{GI,GC,GC,GC,GC,GO,GC,GC,GI},
		{N,GI,GC,GC,GC,GC,GC,GI,N},
		{N,N,GI,GI,GI,GI,GI,N,N}
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

color_t blocks[5][24] = {
		{W,W,N, N, W,N, N, N,W,N, N, W,W, N, W,N,W, N, W,W,N, N, N,N},
		{W,N,W, N, W,N, N, W,N,W, N, W,N, N, W,N,W, N, W,N,N, N, W,N},
		{W,W,N, N, W,N, N, W,N,W, N, W,N, N, W,W,N, N, W,W,W, N, N,N},
		{W,N,W, N, W,N, N, W,N,W, N, W,N, N, W,N,W, N, N,N,W, N, W,N},
		{W,W,N, N, W,W, N, N,W,N, N, W,W, N, W,N,W, N, W,W,W, N, N,N}
};

#define NUMBERS_NUM		10
#define NUMBERS_HEIGHT	5
#define NUMBERS_WIDTH	3
color_t numbers[NUMBERS_NUM][NUMBERS_HEIGHT][NUMBERS_WIDTH] = {
		{
				{W,W,W},
				{W,N,W},
				{W,N,W},
				{W,N,W},
				{W,W,W}
		},
		{
				{W,W,N},
				{N,W,N},
				{N,W,N},
				{N,W,N},
				{W,W,W}
		},
		{
				{N,W,W},
				{N,N,W},
				{W,W,W},
				{W,N,N},
				{W,W,W}
		},
		{
				{N,W,W},
				{N,N,W},
				{N,W,W},
				{N,N,W},
				{W,W,W}
		},
		{
				{W,N,N},
				{W,N,W},
				{W,W,W},
				{N,N,W},
				{N,N,W}
		},
		{
				{W,W,N},
				{W,N,N},
				{W,W,W},
				{N,N,W},
				{W,W,W}
		},
		{
				{W,W,N},
				{W,N,N},
				{W,W,W},
				{W,N,W},
				{W,W,W}
		},
		{
				{W,W,W},
				{N,N,W},
				{N,N,W},
				{N,N,W},
				{N,N,W}
		},
		{
				{W,W,W},
				{W,N,W},
				{W,W,W},
				{W,N,W},
				{W,W,W}
		},
		{
				{W,W,W},
				{W,N,W},
				{W,W,W},
				{N,N,W},
				{N,W,W}
		},
};

// Smoke animation
#define SMOKE_TIME      100	    // miliseconds
#define SMOKE_FRAMES    5
#define SMOKE_WIDTH     3
#define SMOKE_HEIGHT    6

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
