#include <stdio.h>
#include <stdbool.h>
#include "xil_printf.h"
#include "main.h"

// Colors used in the game
const color_t black = N;	  // Background
const color_t light_blue = B; // Ball
const color_t gold = G;		  // Bar

// Global variables
volatile int *gpio0 = (int *)BASE_GPIO0; // dir base buttons

int main()
{
	position_t bar_pos = {((RESOLUTION_X / 2) - BAR_LENGTH / 2), BAR_Y_POS};
	ball_t ball;
	map_t map;
	game_status_t status;
	levels_t level;
	color_t *win_lose_title = NULL;
	int bar_speed, ball_speed;
	int dir;
	int lives;
	int remaining_blocks;
	bool game_finished = false;
	init_buttons();
	init_timer();
	init_leds();

	while (1)
	{
		// Init variables
		bar_speed = 0;
		ball_speed = 0;
		lives = NUM_LIVES;
		status = continues;

		level = level_selection(game_finished, win_lose_title);
		game_finished = false;

		// Prints background
		print_background(black);

		// Print game borders
		print_frame(); // initialize frames
		print_lives(lives, NUM_LIVES, *heart);

		// Print map
		init_map(&map, level);
		print_map(map.blocks);
		remaining_blocks = map.destructible;
		print_blocks_info(remaining_blocks, *blocks, **numbers);

		// Initialize the bar and the ball
		init_ball(&ball, &bar_pos);
		move_bar(0, &bar_pos);
		ball.mov = 3; // default start movement, top left

		while (status == continues)
		{
			// Every 2 time, move the bar along the X-axis
			if (bar_speed == BAR_SPEED)
			{
				bar_speed = 0;
				if ((dir = check_button()) != 0)
					move_bar(dir, &bar_pos);
			}
			else
				bar_speed++;
			// Every 3 times, the ball moves to its next position
			if (ball_speed == BALL_SPEED)
			{
				ball_speed = 0;
				status = move_ball(&ball, &bar_pos, &map);
				if (status == lost_life)
				{
					bar_speed = 0;
					ball_speed = 0;
					lives--;
					if (lives == 0)
						status = game_over;
					else
					{
						status = continues;
						if (ball.mov == 1) // set ball movement for next round
						{
							ball.mov = 0;
						}
						else
						{
							ball.mov = 3;
						}
						reset_bar_position(&bar_pos);
						life_lost(lives, &ball, &bar_pos);
					}
				}
				else if (status == block_broken)
				{
					remaining_blocks--;
					print_blocks_info(remaining_blocks, *blocks, **numbers);
					xil_printf("Remaining blocks: %d\r", remaining_blocks);
					if (remaining_blocks == 0)
						status = win;
					else
						status = continues;
				}
			}
			else
				ball_speed++;
			msleep(10);
		}

		if (status == game_over) // end game, game over
		{
			reset_bar_position(&bar_pos);
			game_finished = true;
			win_lose_title = *game_over_title;
		}
		else if (status == win) // end game, win
		{
			game_win();
			reset_bar_position(&bar_pos);
			game_finished = true;
			win_lose_title = *you_won_title;
		}
	}
	return 0;
}

void game_win()
{
	led_loop(NUM_LED_LAPS);
}

void life_lost(int lives, ball_t *ball, position_t *bar_pos)
{
	position_t ball_pos = {ball->x - SMOKE_WIDTH / 2, ball->y - SMOKE_HEIGHT + 1};
	print_lives(lives, NUM_LIVES, *heart);
	paint_animation(ball_pos, **smoke, SMOKE_FRAMES, SMOKE_TIME, SMOKE_HEIGHT, SMOKE_WIDTH);
	init_ball(ball, bar_pos);
}

void init_buttons()
{
	// Configurar 4 bits como entrada
	gpio0[1] = MASK_BUTTONS;
}

int check_button()
{
	int data;
	char btn = 0; // Default: no button pressed

	// Checks if any button is pressed
	if ((data = gpio0[0] & MASK_BUTTONS) != 0)
	{
		if ((data & 0x2) != 0) 		// Right
			btn = 1;
		else if ((data & 0x4) != 0) // Left
			btn = 3;
		else if ((data & 0x1) != 0) // Top
			btn = 2;
	}

	return btn;
}

void wait_button()
{
	int data;
	while ((data = gpio0[0] & MASK_BUTTONS) != 0)
		msleep(10);
}

game_status_t move_ball(ball_t *ball, position_t *bar_pos, map_t *map)
{
	game_status_t status = continues;
	position_t next_pos;
	side_t side;
	block_t **block_ptr = NULL;
	block_t *block;
	movement_t next_mov;
	bool is_block = false;
	color_t next_color;

	switch (ball->mov)
	{
	case 0: // top right
		next_pos.x = ball->x + 1;
		next_pos.y = ball->y - 1;
		break;
	case 1: // bottom right
		next_pos.x = ball->x + 1;
		next_pos.y = ball->y + 1;
		break;
	case 2: // bottom left
		next_pos.x = ball->x - 1;
		next_pos.y = ball->y + 1;
		break;
	case 3: // top left
		next_pos.x = ball->x - 1;
		next_pos.y = ball->y - 1;
		break;
	}
	next_color = get_color(next_pos.x, next_pos.y);
	if (!equals_color(black, next_color)) // not empty space
	{
		if ((side = calculate_border(next_pos)) == not_border) // block or bar side
		{
			if ((is_block = calculate_block(next_pos, block_ptr, map))) // block
			{
				block = *block_ptr;
				if (!block->indestructible)
				{
					block->collisions--;
					if (block->collisions == 0)
					{
						print_block(block->location, black);
						status = block_broken;
					}
					else
						reprint_block(block);
				}
			}
		}
		else if (side == bottom) // bottom of screen
		{
			paint(ball->x, ball->y, black);
			return lost_life;
		}
		else
			is_block = false;
		next_mov = calculate_rebound(ball, side, is_block, *block, &next_pos, bar_pos);
	}
	else // normal move
	{
		next_mov = ball->mov;
	}
	paint(ball->x, ball->y, black);
	ball->x = next_pos.x;
	ball->y = next_pos.y;
	ball->mov = next_mov;
	paint(ball->x, ball->y, light_blue);

	return status;
}

side_t calculate_border(position_t next_pos)
{
	bool is_left = false, is_right = false, is_top = false, is_bottom = false;
	side_t res;

	if (next_pos.x == INT_X_BORDER)
		is_left = true;
	if (next_pos.x == END_X_BORDER)
		is_right = true;
	if (next_pos.y == INT_Y_BORDER)
		is_top = true;
	if (next_pos.y == END_Y_BORDER)
		is_bottom = true;

	if (is_left)
		if (is_top)
			res = top_left; // top left corner
		else if (is_bottom)
			res = bottom_left; // bottom left corner
		else
			res = left; // left side
	else if (is_right)
		if (is_top)
			res = top_right; // top right corner
		else if (is_bottom)
			res = bottom_right; // bottom right corner
		else
			res = right; // right side
	else if (is_top)
		res = top; // top side
	else if (is_bottom)
		res = bottom; // bottom side
	else
		res = not_border; // not a border

	return res;
}

side_t which_side_block(position_t next_pos, block_t block)
{
	bool is_left = false, is_right = false, is_top = false, is_bottom = false;
	side_t res;

	if (next_pos.x >= block.location.x && next_pos.x < block.location.x + BLOCK_LENGTH &&
		next_pos.y == block.location.y) // top side
		is_top = true;
	if (next_pos.x >= block.location.x && next_pos.x < block.location.x + BLOCK_LENGTH &&
		next_pos.y == block.location.y + BLOCK_HEIGHT - 1) // bottom side
		is_bottom = true;
	if (next_pos.x == block.location.x && next_pos.y >= block.location.y &&
		next_pos.y < block.location.y + BLOCK_HEIGHT) // left side
		is_left = true;
	if (next_pos.x == block.location.x + BLOCK_LENGTH - 1 && next_pos.y >= block.location.y &&
		next_pos.y < block.location.y + BLOCK_HEIGHT) // right side
		is_right = true;

	if (is_left)
		if (is_top) // top left corner
			res = top_left;
		else if (is_bottom) // bottom left corner
			res = bottom_left;
		else
			res = left; // left side
	else if (is_right)
		if (is_top) // top right corner
			res = top_right;
		else if (is_bottom) // bottom right corner
			res = bottom_right;
		else
			res = right; // right side
	else if (is_top)
		res = top; // top side
	else if (is_bottom)
		res = bottom; // bottom side

	return res;
}

side_t which_side_bar(position_t next_pos, position_t *bar_pos)
{
	bool is_left = false, is_right = false, is_top = false;
	side_t res;

	if (next_pos.x >= bar_pos->x && next_pos.x < bar_pos->x + BAR_LENGTH &&
		next_pos.y == bar_pos->y)
		is_top = true;
	if (next_pos.x == bar_pos->x && next_pos.y >= bar_pos->y &&
		next_pos.y < bar_pos->y + BAR_HEIGHT)
		is_left = true;
	if (next_pos.x == bar_pos->x + BAR_LENGTH - 1 && next_pos.y >= bar_pos->y &&
		next_pos.y < bar_pos->y + BAR_HEIGHT)
		is_right = true;

	if (is_left)
		if (is_top)
			res = top_left; // top left corner
		else
			res = left; // left side
	else if (is_right)
		if (is_top)
			res = top_right; // top right corner
		else
			res = right; // right side
	else if (is_top)
		res = top; // top side

	return res;
}

bool calculate_block(position_t next_pos, block_t **block, map_t *map)
{
	for (int i = N_BLOCKS_Y - 1; i >= 0; i--)
	{
		for (int j = N_BLOCKS_X - 1; j >= 0; j--)
		{
			block_t *res = &map->blocks[j][i];
			if (next_pos.x >= res->location.x && next_pos.x < res->location.x + BLOCK_LENGTH &&
				next_pos.y >= res->location.y && next_pos.y < res->location.y + BLOCK_HEIGHT) // inside block
			{
				*block = res;
				return true;
			}
		}
	}
	return false;
}

movement_t calculate_rebound(ball_t *ball, side_t side, bool is_block, block_t block, position_t *next_pos,
							 position_t *bar_pos)
{
	movement_t mov = ball->mov;
	if (side != not_border) // border
	{
		switch (side)
		{
		case top_left:
			mov = mov_bottom_right;
			next_pos->x = ball->x + 1;
			next_pos->y = ball->y + 1;
			break;
		case top_right:
			mov = mov_bottom_left;
			next_pos->x = ball->x - 1;
			next_pos->y = ball->y + 1;
			break;
		case top:
			if (ball->mov == mov_top_right)
			{
				mov = mov_bottom_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y + 1;
			}
			else
			{
				mov = mov_bottom_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y + 1;
			}
			break;
		case left:
			if (ball->mov == mov_top_left)
			{
				mov = mov_top_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_bottom_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y + 1;
			}
			break;
		case right:
			if (ball->mov == mov_top_right)
			{
				mov = mov_top_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_bottom_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y + 1;
			}
			break;
		default:
			break;
		}
	}
	else if (is_block) // block
	{
		switch (which_side_block(*next_pos, block))
		{
		case top_left:
			mov = mov_top_left;
			next_pos->x = ball->x - 1;
			next_pos->y = ball->y - 1;
			break;
		case top_right:
			mov = mov_top_right;
			next_pos->x = ball->x + 1;
			next_pos->y = ball->y - 1;
			break;
		case bottom_left:
			mov = mov_bottom_left;
			next_pos->x = ball->x - 1;
			next_pos->y = ball->y + 1;
			break;
		case bottom_right:
			mov = mov_bottom_right;
			next_pos->x = ball->x + 1;
			next_pos->y = ball->y + 1;
			break;
		case top:
			if (ball->mov == mov_bottom_right)
			{
				mov = mov_top_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_top_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y - 1;
			}
			break;
		case bottom:
			if (ball->mov == mov_top_right)
			{
				mov = mov_bottom_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y + 1;
			}
			else
			{
				mov = mov_bottom_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y + 1;
			}
			break;
		case left:
			if (ball->mov == mov_bottom_right)
			{
				mov = mov_bottom_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y + 1;
			}
			else
			{
				mov = mov_top_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y - 1;
			}
			break;
		case right:
			if (ball->mov == mov_bottom_left)
			{
				mov = mov_top_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_bottom_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y + 1;
			}
			break;
		default:
			break;
		}
	}
	else if (next_pos->y < END_Y_BORDER)
	{
		switch (which_side_bar(*next_pos, bar_pos))
		{
		case top_left:
			mov = mov_top_left;
			next_pos->x = ball->x - 1;
			next_pos->y = ball->y - 1;
			break;
		case top_right:
			mov = mov_top_right;
			next_pos->x = ball->x + 1;
			next_pos->y = ball->y - 1;
			break;
		case top:
			if (ball->mov == mov_bottom_right)
			{
				mov = mov_top_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_top_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y - 1;
			}
			break;
		case left:
			if (ball->mov == mov_bottom_right)
			{
				mov = mov_bottom_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y + 1;
			}
			else
			{
				mov = mov_top_left;
				next_pos->x = ball->x - 1;
				next_pos->y = ball->y - 1;
			}
			break;
		case right:
			if (ball->mov == mov_bottom_left)
			{
				mov = mov_top_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y - 1;
			}
			else
			{
				mov = mov_bottom_right;
				next_pos->x = ball->x + 1;
				next_pos->y = ball->y + 1;
			}
			break;
		default:
			break;
		}
	}
	return mov;
}

void move_bar(int dir, position_t *bar_pos)
{
	int var;

	if (dir == 1) // left
		var = -1;
	else if (dir == 3) // right
		var = 1;
	else
		var = 0; // no movement

	if (bar_pos->x + var > INT_X_BORDER && bar_pos->x + var <= END_X_BORDER - BAR_LENGTH)
	{
		rect(*bar_pos, black, BAR_LENGTH, BAR_HEIGHT);
		bar_pos->x = bar_pos->x + var;
		rect(*bar_pos, gold, BAR_LENGTH, BAR_HEIGHT);
	}
}

void init_ball(ball_t *ball, position_t *bar_pos)
{
	ball->x = bar_pos->x + BAR_LENGTH / 2;
	ball->y = bar_pos->y - 1;
	paint(ball->x, ball->y, light_blue);
}

levels_t level_selection(bool game_finished, color_t *win_lose_title)
{
	int btn = 0;
	levels_t level;

	print_background(black);

	position_t aux = {57, 25};
	paint_object(aux, *choose_level, 5, 47);
	aux.x = 50;
	aux.y = 50;
	paint_object(aux, *number_1_level, 12, 9);
	aux.y = 65;
	paint_object(aux, *button_left, 10, 9);
	aux.x = 75;
	aux.y = 40;
	paint_object(aux, *number_2_level, 12, 10);
	aux.y = 55;
	paint_object(aux, *button_top, 10, 9);
	aux.x = 100;
	aux.y = 50;
	paint_object(aux, *number_3_level, 12, 9);
	aux.y = 65;
	paint_object(aux, *button_right, 10, 9);
	aux.x = 5;
	aux.y = 100;
	paint_object(aux, *authors, 14, 25);
	aux.x = 61;
	aux.y = 10;
	paint_object(aux, *breakout, 7, 38);

	if (game_finished)
	{
		aux.x = 57;
		aux.y = 85;
		paint_object(aux, win_lose_title, 5, 46); // paint string
	}

	while (btn == 0)
		btn = check_button(); // wait for release button

	switch (btn)
	{
	case 1: // first level
		level = first_lvl;
		aux.x = 50;
		aux.y = 65;
		paint_object(aux, *button_left_pressed, 10, 9);
		break;
	case 2: // second level
		level = second_lvl;
		aux.x = 75;
		aux.y = 55;
		paint_object(aux, *button_top_pressed, 10, 9);
		break;
	case 3: // third level
		level = third_lvl;
		aux.x = 100;
		aux.y = 65;
		paint_object(aux, *button_right_pressed, 10, 9);
		break;
	default:
		break;
	}
	wait_button(); // wait for release button
	msleep(200); // wait 200 ms
	return level;
}

void reset_bar_position(position_t *bar_pos)
{
	rect(*bar_pos, black, BAR_LENGTH, BAR_HEIGHT);
	bar_pos->x = ((RESOLUTION_X / 2) - BAR_LENGTH / 2);
	rect(*bar_pos, gold, BAR_LENGTH, BAR_HEIGHT);
}
