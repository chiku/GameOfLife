#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graphics.h"

void cleanup_on_signal() { }

void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_At((Graphics*)data, x, y);
}

