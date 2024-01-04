#ifndef __MAIN_H__
#define __MAIN_H__

#include "blocks.h"
#include "colors.h"
#include "graphics.h"
#include "peripherals/timer.h"
#include "peripherals/leds.h"
#include "peripherals/buttons.h"

// Ball specification
#define BALL_SPEED		3
typedef enum movement {mov_top_right, mov_bottom_right, mov_bottom_left, mov_top_left} movement_t;

// Bar specification
#define BAR_LENGTH		13
#define BAR_HEIGHT		2
#define BAR_SPEED		2
#define BAR_Y_POS		90
typedef enum directions {bar_no_dir, bar_dir_left, bar_dir_right} bar_direction_t;

// Game parameters
#define NUM_LIVES		3
#define NUM_LED_LAPS	3

// Smoke animation
#define SMOKE_TIME      100	    // miliseconds
#define SMOKE_FRAMES    5
#define SMOKE_WIDTH     3
#define SMOKE_HEIGHT    6

// Remaining blocks numbers
#define NUMBERS_NUM		10
#define NUMBERS_HEIGHT	5
#define NUMBERS_WIDTH	3

typedef enum game_status {continues, lost_life, block_broken, win, game_over} game_status_t;

typedef enum side {not_border, top, bottom, right, left,
						top_left, top_right, bottom_left, bottom_right} side_t;

typedef struct ball {
	int x, y;
	movement_t mov;
} ball_t;


/**
 * @brief Shows the level selection screen.
 *
 * This function shows the level selection screen and allows the user to select a level.
 *
 * @param game_finished A boolean value indicating whether the game has finished or not.
 * @param win_lose_title Pointer to the color variable that stores the structs of color_t of string "You won!" or "Game over:)".
 * @return The selected level.
 */
levels_t level_selection(bool game_finished, color_t *win_lose_title);

/**
 * Handles the event when a life is lost.
 * @param lives The current number of lives.
 * @param ball Pointer to the ball object.
 * @param bar_pos Pointer to the position of the bar.
 */
void life_lost(int lives, ball_t *ball, position_t *bar_pos);

/**
 * Handles the event when the game is won.
 */
void game_win();


// BALL FUNCTIONS DECLARATION

/**
 * Initializes the ball object with the given bar position.
 *
 * @param ball The ball object to be initialized.
 * @param bar_pos The position of the bar.
 */
void init_ball(ball_t *ball, position_t *bar_pos);

/**
 * @brief Moves the ball on the game board.
 *
 * This function updates the position of the ball based on its current velocity and checks for collisions with the bar and the walls of the game board.
 *
 * @param ball Pointer to the ball object.
 * @param bar_pos Pointer to the position of the bar.
 * @param map Pointer to the game map.
 * @return The game status after moving the ball.
 */
game_status_t move_ball(ball_t *ball, position_t *bar_pos, map_t *map);

/**
 * Calculates the rebound of a ball based on the given parameters.
 *
 * @param ball      Pointer to the ball object.
 * @param side      The side of the collision.
 * @param is_block  Indicates if the collision is with a block.
 * @param block     The block object involved in the collision.
 * @param next_pos  Pointer to the next position of the ball after the rebound.
 * @param bar_pos   Pointer to the position of the bar.
 *
 * @return The movement type of the rebound.
 */
movement_t calculate_rebound(ball_t *ball, side_t side, bool is_block, block_t block, position_t *next_pos, position_t *bar_pos);

/**
 * @brief Calculates the border for the next position.
 *
 * This function takes a position as input and calculates the border for the next position.
 * The calculated border is returned as a side_t value.
 *
 * @param next_pos The next position for which the border needs to be calculated.
 * @return The calculated border as a side_t value.
 */
side_t calculate_border(position_t next_pos);

/**
 * Determines which side of the block the next position is on.
 *
 * @param next_pos The next position to check.
 * @param block The block to compare against.
 * @return The side of the block that the next position is on.
 */
side_t which_side_block(position_t next_pos, block_t block);


// BAR FUNCTIONS DECLARATION

/**
 * Initializes the position of the bar.
 * @param bar_pos Pointer to the position of the bar.
 */
void init_bar(position_t *bar_pos);

/**
 * @brief Moves the bar in the specified direction.
 *
 * This function updates the position of the bar based on the specified direction.
 *
 * @param dir The direction in which to move the bar. Use a 3 to move right, and a 1 to move left.
 * @param bar_pos Pointer to the position of the bar.
 */
void move_bar(bar_direction_t dir, position_t *bar_pos);

/**
 * Determines which side of the bar the next position is on.
 *
 * @param next_pos The next position to check.
 * @param bar_pos  The current position of the bar.
 * @return The side of the bar that the next position is on.
 */
side_t which_side_bar(position_t next_pos, position_t *bar_pos);



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

// Remaining blocks title
color_t blocks[5][24] = {
	{W,W,N, N, W,N, N, N,W,N, N, W,W, N, W,N,W, N, W,W,N, N, N,N},
	{W,N,W, N, W,N, N, W,N,W, N, W,N, N, W,N,W, N, W,N,N, N, W,N},
	{W,W,N, N, W,N, N, W,N,W, N, W,N, N, W,W,N, N, W,W,W, N, N,N},
	{W,N,W, N, W,N, N, W,N,W, N, W,N, N, W,N,W, N, N,N,W, N, W,N},
	{W,W,N, N, W,W, N, N,W,N, N, W,W, N, W,N,W, N, W,W,W, N, N,N}
};

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

// You won title
color_t you_won_title[5][46] = {
	{N,N,N,N,N,N, N, W,N,W, N, W,W,W, N, W,N,W, N, N,N,N, N, W,N,N,N,W, N, W,W,W, N, W,N,N,N,W, N, W, N, N,N,N,N,N},
	{N,N,N,N,N,N, N, W,N,W, N, W,N,W, N, W,N,W, N, N,N,N, N, W,N,N,N,W, N, W,N,W, N, W,W,N,N,W, N, W, N, N,N,N,N,N},
	{N,N,N,N,N,N, N, W,W,W, N, W,N,W, N, W,N,W, N, N,N,N, N, W,N,N,N,W, N, W,N,W, N, W,N,W,N,W, N, W, N, N,N,N,N,N},
	{N,N,N,N,N,N, N, N,N,W, N, W,N,W, N, W,N,W, N, N,N,N, N, W,N,W,N,W, N, W,N,W, N, W,N,N,W,W, N, N, N, N,N,N,N,N},
	{N,N,N,N,N,N, N, W,W,W, N, W,W,W, N, W,W,W, N, N,N,N, N, N,W,N,W,N, N, W,W,W, N, W,N,N,N,W, N, W, N, N,N,N,N,N}
};

// Game over title
color_t game_over_title[5][46] = {
	{W,W,W, N, W,W,W, N, W,N,N,N,W, N, W,W,W, N, N,N,N, N, W,W,W, N, W,N,W, N, W,W,W, N, W,W,W, N, N,N,N, N, N,N,N,W},
	{W,N,N, N, W,N,W, N, W,W,N,W,W, N, W,N,N, N, N,N,N, N, W,N,W, N, W,N,W, N, W,N,N, N, W,N,W, N, N,N,N, N, W,N,W,N},
	{W,N,W, N, W,W,W, N, W,N,W,N,W, N, W,W,W, N, N,N,N, N, W,N,W, N, W,N,W, N, W,W,W, N, W,W,N, N, N,N,N, N, N,N,W,N},
	{W,N,W, N, W,N,W, N, W,N,N,N,W, N, W,N,N, N, N,N,N, N, W,N,W, N, W,N,W, N, W,N,N, N, W,N,W, N, N,N,N, N, W,N,W,N},
	{W,W,W, N, W,N,W, N, W,N,N,N,W, N, W,W,W, N, N,N,N, N, W,W,W, N, N,W,N, N, W,W,W, N, W,N,W, N, N,N,N, N, N,N,N,W}
};

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
