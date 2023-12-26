#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

const color_t map_colors[N_BLOCKS_Y] = {M_RED, M_ORANGE, M_YELLOW, M_GREEN, M_DBLUE, M_PURPLE, M_CYAN};

void print_block(position_t pos, color_t col)
{
	int i, j;    

	for(i = 0; i < BLOCK_LENGTH; i++)
		for(j = 0; j < BLOCK_HEIGHT; j++)
			paint(pos.x + i, pos.y + j, col);
}

/**
 * @brief Reprints a block on the screen after a collision.
 * This function takes a block as input and reprints it with a lighter color.
 *
 * @param block The block to be reprinted.
 */
void reprint_block(block_t block)
{
    block.color.r -= BLOCK_COLOR_DIFF;
    block.color.g -= BLOCK_COLOR_DIFF;
    block.color.b -= BLOCK_COLOR_DIFF;

    print_block(block.location, block.color);
}

void init_map(block_t map[N_BLOCKS_X][N_BLOCKS_Y], levels_t level)
{
	int i, j, collisions;
    color_t indest_color = M_DGREY;

	for(i = 0; i < N_BLOCKS_Y; i++)
    {
		for(j = 0; j < N_BLOCKS_X; j++)
        {
            if (level == third_lvl)
            	map[j][i].indestructible = (rand() % 4 == 0) ? true : false;  // approx. 25% of indestructible blocks
            else
            	map[j][i].indestructible = false;

            if (map[j][i].indestructible)
            {
                map[j][i].collisions = 0;
                map[j][i].color = indest_color;
            }
            else
            {
                if (level == second_lvl)
                    collisions = (rand() % 10 < 7) ? 1 : (rand() % 10 < 9) ? 2 : 3;  // 70% chance for 1, 15% chance for 2, 15% chance for 3
                else
                    collisions = 1;

                map[j][i].collisions = collisions;
                map[j][i].color = map_colors[i];
                map[j][i].color.r = map_colors[i].r + (collisions - 1) * BLOCK_COLOR_DIFF;
                map[j][i].color.g = map_colors[i].g + (collisions - 1) * BLOCK_COLOR_DIFF;
                map[j][i].color.b = map_colors[i].b + (collisions - 1) * BLOCK_COLOR_DIFF;
            }
            map[j][i].i = i;
            map[j][i].j = j;
        }
    }
}

void print_map(struct block map[N_BLOCKS_X][N_BLOCKS_Y])
{
	int i, j;
    position_t pos;

	for(i = 0; i < N_BLOCKS_Y; i++)
    {
        pos.x = SEPARATION + 2;
        pos.y = SEPARATION + i * (BLOCK_HEIGHT + SEPARATION) + 2;

		for(j = 0; j < N_BLOCKS_X; j++)
        {
            pos.x = SEPARATION + j * (BLOCK_LENGTH + SEPARATION) + 2;
			map[j][i].location.x = pos.x;
			map[j][i].location.y = pos.y;
            print_block(pos, map[j][i].color);
        }
    }
}
