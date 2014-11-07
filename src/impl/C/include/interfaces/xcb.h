#ifndef GOL_INTERFACE_XCB_GRAPHICS_H
#define GOL_INTERFACE_XCB_GRAPHICS_H

#define SCREEN 800
#define SQUARE 5

#include <xcb/xcb.h>
#include "base.h"

struct Graphics
{
	xcb_connection_t *connection;
	xcb_screen_t *screen;
	xcb_window_t window;
	xcb_gcontext_t current_context, alive_context, dead_context;
	xcb_colormap_t colourmap;
	uint32_t alive_colour, dead_colour;
};

#endif
