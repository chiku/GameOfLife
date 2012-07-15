#ifndef GOL_INTERFACE_CURSES_GRAPHICS_H
#define GOL_INTERFACE_CURSES_GRAPHICS_H

#include "base.h"

struct Graphics
{
	int drawing_symbol;
	int alive_colour, dead_colour;
	int draw_colour_palate, erase_colour_palate;
};

#endif
