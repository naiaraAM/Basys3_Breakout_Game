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

#define INT_X_BORDER		1
#define END_X_BORDER		158
#define INT_Y_BORDER		1
#define END_Y_BORDER		118
#define BORDER_THICKNESS	1

#define BAR_LENGTH			13
#define BAR_HEIGHT			2

#define NUM_LIFES			3


/*
color_t bar[BAR_LENGTH][BAR_HEIGHT]={
		{G,G,G,G,G,G,G,G,G,G,G},
		{G,G,G,G,G,G,G,G,G,G,G}
};
*/

color_t number_1[12][9]={
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
color_t number_2[12][10]={
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
color_t number_3[12][9]={
    {N,N,GI,GI,GI,GI,GI,N,N},
	{N,GI,W,W,W,W,GC,GI,N},
	{GI,W,W,W,W,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC,GI},
	{GI,W,W,GC,GI,GI,W,W,GC,GI},
	{N,GI,GI,GI,W,W,W,GC,GI,N},
	{N,GI,GI,GI,W,W,W,GC,GI,N},
	{GI,W,W,GC,GI,GI,W,W,GC,GI},
	{GO,W,W,GC,GO,GO,W,W,GC,GO},
	{GO,W,W,W,W,W,W,GC,GO},
	{N,GO,W,W,W,W,W, GC,GO,N},
	{N,N,GO,GO,GO,GO,GO,N,N}

};

color_t button[10][9]={
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

color_t choose_level[5][47]={
		{W,W,W,N,W,N,W,N,W,W,W,N,W,W,W,N,W,W,W,N,W,W,W,N,N,N,W,N,N,N,W,W,W,N,W,N,W,N,W,W,W,N,W,N,N,N,N},
		{W,N,N,N,W,N,W,N,W,N,W,N,W,N,W,N,W,N,N,N,W,N,N,N,N,N,W,N,N,N,W,N,N,N,W,N,W,N,W,N,N,N,W,N,N,N,W},
		{W,N,N,N,W,W,W,N,W,N,W,N,W,N,W,N,W,W,W,N,W,W,N,N,N,N,W,N,N,N,W,W,N,N,W,N,W,N,W,W,N,N,W,N,N,N,N},
		{W,N,N,N,W,N,W,N,W,N,W,N,W,N,W,N,N,N,W,N,W,N,N,N,N,N,W,N,N,N,W,N,N,N,W,N,W,N,W,N,N,N,W,N,N,N,W},
		{W,W,W,N,W,N,W,N,W,W,W,N,W,W,W,N,W,W,W,N,W,W,W,N,N,N,W,W,W,N,W,W,W,N,N,W,N,N,W,W,W,N,W,W,W,N,N}
};

color_t authors[14][25]={
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

color_t smoke[SMOKE_FRAMES][SMOKE_WIDTH][SMOKE_HEIGHT] = {
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
        {G_BL,G_BL,G_BL},
        {G_GO,G_BL,G_BL},
        {G_BL,G_GO,G_GC},
        {G_GC,G_BL,G_GO},
        {G_BL,G_BL,G_BL}
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
        {G_BL,G_BL,G_GO},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL},
        {G_BL,G_BL,G_BL}
    }
};

color_t breakout[7][38] = {
		{W,W,W,N, N, W,W,W,N, N, W,W,W,W, N, W,W,W,W, N, W,N,N,W, N, W,W,W,W, N, W,N,N,W, N, W,W,W},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,W,W,N, N, W,W,W,N, N, W,W,W,N, N, W,W,W,W, N, W,W,N,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,W,N, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,N,N,W, N, W,N,N,W, N, W,N,N,N, N, W,N,N,W, N, W,N,W,N, N, W,N,N,W, N, W,N,N,W, N, N,W,N},
		{W,W,W,N, N, W,N,N,W, N, W,W,W,W, N, W,N,N,W, N, W,N,N,W, N, W,W,W,W, N, W,W,W,W, N, N,W,N}
};



// Funci�n que pinta una imagen en la VGA.
// Solo pinta los puntos que no son de color alfa (en este caso, negro), que se quedan "transparentes".


// Mueve la n�ve autom�ticamente de derecha a izquierda o viceversa
// El procedimiento para mover la nave es:
//        borrar la nave de pantalla, calcular la nueva posici�n, pintar la nave
void move_bar(int dir);

// Inicializa una bala en la posici�n X
void init_ball();

// Mueve la bala, en vertical, hasta y = 0. Cuando llega ah� la desactiva
game_status_t move_ball();

void init_buttons();

int wait_button();

side_t calculate_border(position_t next_pos);
bool calculate_block(position_t next_pos, block_t *block);
movement_t calculate_rebound(ball_t bola, side_t side, bool is_block, block_t *block, position_t *next_pos);
side_t which_side_bar(position_t next_pos);
levels_t level_selection();
void life_lost();

#endif
