#ifndef __MAIN_H__
#define __MAIN_H__

#include "blocks.h"

#define VGA_CTRL_BASE 0x44A00000


typedef struct ball {
	int x, y, mov;
} ball_t;

typedef enum side {top, bottom, right, left,
					top_left, top_right, bottom_left, bottom_right,
					not_border} side_t;

typedef enum movement {mov_top_right, mov_bottom_right, mov_bottom_left, mov_top_left} movement_t;

typedef enum game_status {continues, life_lost, block_broken, win, game_over} game_status_t;

/**
 * LEVEL DESCRIPTION:
 * Every level has a different map, and the same lives.
 * 1. Every block in the map can be broken with one hit.
 * 2. The same than lvl 1, but random blocks in the map will increase their collision requirements.
 * 3. The same than lvl 2, plus random indestructible blocks.
*/
typedef enum levels {first_lvl, second_lvl, third_lvl} levels_t;

#define A {0x00, 0x00, 0xf0}
#define C {0x00, 0x80, 0x00}
#define D {0x00, 0xf0, 0x00}
#define E {0xf0, 0xf0, 0x00}
#define F {0xf0, 0x00, 0x00}
#define W {0xff, 0xff, 0xff}
#define G {0xc2, 0x99, 0x27}
#define B {0xb4, 0xe2, 0xf4}
#define N {0x00, 0x00, 0x00}
#define GO {0x3d, 0x3d, 0x3d}
#define GI {0x78, 0x78, 0x78}
#define GC {0xb0, 0xac, 0xb0}

#define INT_X_BORDER		1
#define END_X_BORDER		158
#define INT_Y_BORDER		1
#define END_Y_BORDER		118
#define BORDER_THICKNESS	1

#define BAR_LENGTH			13
#define BAR_HEIGHT			2

#define NUM_LIFES			3

color_t negro = N;
color_t blanco = W;
color_t azul = A;
color_t azul_claro = B;
color_t verde = C;
color_t verde_oscuro = D;
color_t amarillo = E;
color_t rojo = F;
color_t gold = G;
color_t gris_claro = GC;
color_t gris_intermedio = GI;
color_t gris_oscuro = GO;


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



// Funci�n que pinta un pixel en pantalla
// X entre 0 y 159, Y entre 0 y 119,
// R/G/B: colores - entre 0 y 255 (los cuatro bits menos significativos se ignoran)
void paint(int x, int y, color_t rgb);

// Funci�n que retorna el valor de un pixel en pantalla
color_t pixel(int x, int y);

// Funci�n que pinta un rect�ngulo de un color
// Pos: esquina superior izquierda del rectangulo
// Color: color del rect�ngulo
// W: anchura, H: altura
void rect (position_t pos, color_t col, int w, int h);


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

int equals_color(color_t color1, color_t color2);

side_t calculate_border(position_t next_pos);
bool calculate_block(position_t next_pos, block_t *block);
movement_t calculate_rebound(ball_t bola, side_t side, bool is_block, block_t *block, position_t *next_pos);
side_t which_side_bar(position_t next_pos);
void paint_object(position_t pos, color_t *object, int height, int width);
int level_selection();

#endif
