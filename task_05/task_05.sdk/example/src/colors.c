#include <stdio.h>
#include "colors.h"

int equals_color(color_t color1, color_t color2)
{
	return ((color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b));
}
