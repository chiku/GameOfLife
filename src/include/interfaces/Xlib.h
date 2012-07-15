#ifndef GOL_INTERFACE_XLIB_GRAPHICS_H
#define GOL_INTERFACE_XLIB_GRAPHICS_H

#define SCREEN 800
#define SQUARE 5

#include <X11/Xlib.h>
#include "base.h"

struct Graphics
{
	Display *display;
	int screen;
	Window window;
	XColor alive, dead;
	GC current_gc, draw_gc, erase_gc;
};

#endif
