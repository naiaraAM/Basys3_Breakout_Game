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

void init_map(map_t *map, levels_t level)
{
	int i, j, collisions = 1, destructibles = N_BLOCKS_X * N_BLOCKS_Y;
    color_t indest_color = M_DGREY;

	for(i = 0; i < N_BLOCKS_Y; i++)
    {
		for(j = 0; j < N_BLOCKS_X; j++)
        {
            // Set block default color
            map->blocks[j][i].color = map_colors[i];

            // Decide if the block is indestructible
            if (level == third_lvl)
            	map->blocks[j][i].indestructible = (rand() % 4 == 0) ? true : false;  // approx. 25% of indestructible blocks
            else
            	map->blocks[j][i].indestructible = false;

            if (map->blocks[j][i].indestructible)
            {
            	map->blocks[j][i].collisions = 0;
            	map->blocks[j][i].color = indest_color;
            	destructibles--;
            }
            else if (level == second_lvl || level == third_lvl)
            {
                collisions = (rand() % 10 < 7) ? 1 : (rand() % 10 < 9) ? 2 : 3;  // 70% chance for 1, 15% chance for 2, 15% chance for 3
                map->blocks[j][i].color.r = map_colors[i].r + (collisions - 1) * BLOCK_COLOR_DIFF;
                map->blocks[j][i].color.g = map_colors[i].g + (collisions - 1) * BLOCK_COLOR_DIFF;
                map->blocks[j][i].color.b = map_colors[i].b + (collisions - 1) * BLOCK_COLOR_DIFF;
            }

            map->blocks[j][i].collisions = collisions;
            map->blocks[j][i].i = i;
            map->blocks[j][i].j = j;
        }
    }
	map->destructible = destructibles;
}

void print_map(block_t blocks[N_BLOCKS_X][N_BLOCKS_Y])
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
            blocks[j][i].location.x = pos.x;
            blocks[j][i].location.y = pos.y;
            print_block(pos, blocks[j][i].color);
        }
    }
}
