#include <stdio.h>
#include "graphics.h"

void print_background(color_t color) {
    for(i=0;i<160;i++)
    	for(j=0;j<120;j++)
    		paint(i,j,negro);
}

void paint_object(position_t pos, color_t *object, int rows, int cols) {
    // Process the array elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
			paint(pos.x + j, pos.y + i, object[i * cols + j]);
        }
    }
}

void paint_animation(position_t pos, color_t ***animation, int frames, int period, int rows, int cols) {
    // Process the frames
    for (int f = 0; f < frames - 1; f++)
        paint_object(pos, animation[f], rows, cols);
    paint_object(pos, animation[frames - 1], rows, cols);
}
