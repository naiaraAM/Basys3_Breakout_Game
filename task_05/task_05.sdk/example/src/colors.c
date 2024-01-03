#include <stdio.h>
#include "colors.h"

bool equals_color(color_t color_1, color_t color_2)
{
	return ((color_1.r == color_2.r) && (color_1.g == color_2.g) && (color_1.b == color_2.b));
}
