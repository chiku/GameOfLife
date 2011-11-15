#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include "graphics.h"

/* Private */
static Display *initialize_display(void)
{
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		printf("Cannot open display\n");
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

	XSelectInput(self->display, self->window, ExposureMask);
	XMapWindow(self->display, self->window);

	return self;
}

void Graphics_Destroy(Graphics *self)
{
	XCloseDisplay(self->display);
	free(self);
}

void Graphics_Start_Loop(Graphics *self)
{
	XEvent event;
	do {
		XNextEvent(self->display, &event);
	} while(event.type != Expose);
}

void Graphics_Draw_Rectangle(Graphics *self, long int x, long int y)
{
	XFillRectangle(self->display,
		self->window,
		DefaultGC(self->display, self->screen),
		SCREEN / 2 + x * SQUARE,
		SCREEN / 2 + y * SQUARE,
		SQUARE, SQUARE);
}

void Graphics_Set_Foreground(Graphics *self)
{
	XSetForeground(self->display, DefaultGC(self->display, self->screen), BlackPixel(self->display, self->screen));
}

void Graphics_Set_Reverse_Foreground(Graphics *self)
{
	XSetForeground(self->display, DefaultGC(self->display, self->screen), WhitePixel(self->display, self->screen));
}
