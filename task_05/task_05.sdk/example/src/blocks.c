#include <stdio.h>
#include "blocks.h"

const color_t map_colors[N_BLOCKS_Y] = {M_RED, M_ORANGE, M_YELLOW, M_GREEN, M_DBLUE, M_PURPLE, M_CYAN};

void print_block(position_t pos, color_t col)
{
	int i, j;    

	for(i = 0; i < BLOCK_LENGTH; i++)
		for(j = 0; j < BLOCK_HEIGHT; j++)
			paint(pos.x + i, pos.y + j, col);
}

void init_map(struct block map[N_BLOCKS_X][N_BLOCKS_Y])
{
	int i, j;    

	for(i = 0; i < N_BLOCKS_Y; i++)
    {
		for(j = 0; j < N_BLOCKS_X; j++)
        {
            map[j][i].color = map_colors[i];
            map[j][i].collisions = 1;
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
			//xil_printf("map[%d][%d]  x: %d; y: %d\n\r", j, i , map[j][i].location.x, map[j][i].location.y);
            print_block(pos, map[j][i].color);
        }
    }
}
