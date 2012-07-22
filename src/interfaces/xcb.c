#define _POSIX_C_SOURCE 199506L

#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>

#include "interfaces/xcb.h"

/* Private */
static xcb_connection_t* Connection_New()
{
	xcb_connection_t* connection = xcb_connect(NULL, NULL);

	if (xcb_connection_has_error(connection)) {
		fprintf(stderr, "Cannot open display!\n");
		exit(2);
	}

	return connection;
}

static xcb_screen_t* Screen_New(xcb_connection_t* connection)
{
	return xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
}

static xcb_window_t Window_New(xcb_connection_t* connection, xcb_screen_t* screen)
{
	uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[2];
	xcb_window_t window = xcb_generate_id(connection);

	values[0] = screen->white_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
	xcb_create_window(connection, screen->root_depth, window, screen->root,
	                  0, 0, SCREEN, SCREEN, 1,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
	                  mask, values);
	return window;
}

static void Graphics_Create_ColorPallate(Graphics *self)
{
	xcb_alloc_color_reply_t *reply;

	xcb_create_colormap(self->connection,
	                    XCB_COLORMAP_ALLOC_NONE,
	                    self->colourmap,
	                    self->window,
	                    self->screen->root_visual);

	reply = xcb_alloc_color_reply(self->connection,
	                              xcb_alloc_color(self->connection, self->colourmap,
	                                              65025, 34952, 4369),
	                              NULL);
	if (!reply) {
		fprintf(stderr, "Cannot set colours!\n");
		exit(2);
	}
	self->alive_colour = reply->pixel;
	free(reply);

	reply = xcb_alloc_color_reply(self->connection,
	                              xcb_alloc_color(self->connection, self->colourmap,
	                                              52428, 52428, 52428),
	                              NULL);
	if (!reply) {
		fprintf(stderr, "Cannot set colours!\n");
		exit(2);
	}
	self->dead_colour = reply->pixel;
	free(reply);
}

static void Graphics_Create_Context(Graphics *self)
{
	uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	uint32_t alive_values[2], dead_values[2];
	xcb_window_t window = self->screen->root;

	self->alive_context = xcb_generate_id(self->connection);
	self->dead_context = xcb_generate_id(self->connection);
	alive_values[0] = self->alive_colour;
	dead_values[0] = self->dead_colour;
	alive_values[1] = 0;
	dead_values[1] = 0;

	xcb_create_gc(self->connection, self->alive_context, window, mask, alive_values);
	xcb_create_gc(self->connection, self->dead_context, window, mask, dead_values);
}
/* Private */

Graphics *Graphics_Allocate()
{
	Graphics *self = (Graphics*) (malloc( sizeof(Graphics) ));

	self->connection = Connection_New();
	self->screen = Screen_New(self->connection);
	self->window = Window_New(self->connection, self->screen);
	self->colourmap = xcb_generate_id(self->connection);

	Graphics_Create_ColorPallate(self);
	Graphics_Create_Context(self);

	return self;
}

Graphics *Graphics_Initialize(Graphics *self)
{
	xcb_map_window(self->connection, self->window);
	xcb_flush(self->connection);
	self->current_context = self->alive_context;
	return self;
}

Graphics *Graphics_New()
{
	return Graphics_Initialize(Graphics_Allocate());
}

void Graphics_Destroy(Graphics *self)
{
	xcb_disconnect(self->connection);
	free(self);
}

void Graphics_Draw_At(const Graphics *self, long int x, long int y)
{
	xcb_rectangle_t rectangle = {
		SCREEN / 2 + x * SQUARE,
		SCREEN / 2 - y * SQUARE,
		SQUARE - 1,
		SQUARE - 1
	};

	xcb_poly_fill_rectangle(self->connection,
	                        self->window,
	                        self->current_context,
	                        1,
	                        &rectangle);
}

void Graphics_Flush(const Graphics *self)
{
	xcb_flush(self->connection);
}

void Graphics_Set_Draw_Color(Graphics *self)
{
	self->current_context = self->alive_context;
}

void Graphics_Set_Erase_Color(Graphics *self)
{
	self->current_context = self->dead_context;
}

/* Signal handling */
void cleanup_on_signal() {}
