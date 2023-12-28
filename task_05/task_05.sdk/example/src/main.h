#ifndef __MAIN_H__
#define __MAIN_H__

#include "blocks.h"
#include "colors.h"
#include "graphics.h"


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

// Game parameters
#define NUM_LIFES			3

// Function definitions
void move_bar(int dir);
void init_ball();
game_status_t move_ball();
void init_buttons();
int check_button();
side_t calculate_border(position_t next_pos);
bool calculate_block(position_t next_pos, block_t **block);
movement_t calculate_rebound(ball_t bola, side_t side, bool is_block, block_t block, position_t *next_pos);
side_t which_side_bar(position_t next_pos);
levels_t level_selection();
void life_lost(int lives);

#endif
