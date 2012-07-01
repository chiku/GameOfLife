#define _POSIX_C_SOURCE 199506L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>

#include "interfaces/Xlib.h"

/* Private */
static Display *initialize_display(void)
{
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display!\n");
		exit(2);
	}
	return display;
}

static Window initialize_window(Display *display, int screen)
{
	return XCreateSimpleWindow(display,
		RootWindow(display, screen),
		10, 10, SCREEN, SCREEN, 1,
		BlackPixel(display, screen),
		WhitePixel(display, screen));
}

static Graphics *Graphics_Create()
{
	return (Graphics*) (malloc( sizeof(Graphics) ));
}
/* Private */

Graphics *Graphics_Initialize()
{
	Graphics *self = Graphics_Create();
	self->display = initialize_display();
	self->screen = DefaultScreen(self->display);
	self->window = initialize_window(self->display, self->screen);

	self->orange_gc = XCreateGC(self->display, self->window, self->screen, NULL);
	self->grey_gc = XCreateGC(self->display, self->window, self->screen, NULL);

	Colormap colormap_orange = DefaultColormap(self->display, self->screen);
	Colormap colormap_grey = DefaultColormap(self->display, self->screen);

	XParseColor(self->display, colormap_orange, "#FF8811", &(self->orange));
	XParseColor(self->display, colormap_grey, "#CCCCCC", &(self->grey));
	XAllocColor(self->display, colormap_orange, &(self->orange));
	XAllocColor(self->display, colormap_grey, &(self->grey));

	XSelectInput(self->display, self->window, ExposureMask);
	XMapWindow(self->display, self->window);
	XStoreName(self->display, self->window, "Conway's Game of Life");

	self->current_gc = self->orange_gc;

	return self;
}

void Graphics_Destroy(Graphics *self)
{
	XCloseDisplay(self->display);
	free(self);
}

void Graphics_Draw_At(Graphics *self, long int x, long int y)
{
	XFillRectangle(self->display,
		self->window,
		self->current_gc,
		SCREEN / 2 + x * SQUARE,
		SCREEN / 2 - y * SQUARE,
		SQUARE - 1, SQUARE - 1);
}

void Graphics_Flush(Graphics *self)
{
	XFlush(self->display);
}

void Graphics_Callback_Handler(Graphics *self, double time_in_s)
{
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = time_in_s * 1000000000L;
	nanosleep(&tim, NULL);
}

void Graphics_Clear(Graphics *self) {}

void Graphics_Set_Draw_Color(Graphics *self)
{
	self->current_gc = self->orange_gc;
	XSetForeground(self->display, self->current_gc, self->orange.pixel);
}

void Graphics_Set_Erase_Color(Graphics *self)
{
	self->current_gc = self->grey_gc;
	XSetForeground(self->display, self->current_gc, self->grey.pixel);
}

/* Signal handling */
void cleanup_on_signal() {}

