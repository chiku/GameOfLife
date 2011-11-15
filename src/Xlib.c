#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>

#include <game_of_life.h>

#include "signal_handlers.c"

#define SCREEN 800
#define SQUARE 5

void handle_signal_for(char *message, int exit_status)
{
	printf(message);
	exit(exit_status);
}

typedef struct Graphics Graphics;

struct Graphics {
	Display *display;
	int screen;
	Window window;
};

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

static Graphics *Graphics_Initialize(){
	Graphics *self = Graphics_Create();
	self->display = initialize_display();
	self->screen = DefaultScreen(self->display);
	self->window = initialize_window(self->display, self->screen);

	XSelectInput(self->display, self->window, ExposureMask);
	XMapWindow(self->display, self->window);

	return self;
}

static void Graphics_Destroy(Graphics *self)
{
	XCloseDisplay(self->display);
	free(self);
}

static void Graphics_Start_Loop(Graphics *self)
{
	XEvent event;
	do {
		XNextEvent(self->display, &event);
	} while(event.type != Expose);
}

static void Graphics_Draw_Rectangle(Graphics *self, long int x, long int y)
{
	XFillRectangle(self->display,
		self->window,
		DefaultGC(self->display, self->screen),
		SCREEN / 2 + x * SQUARE,
		SCREEN / 2 + y * SQUARE,
		SQUARE, SQUARE);
}

static void Graphics_Set_Foreground(Graphics *self)
{
	XSetForeground(self->display, DefaultGC(self->display, self->screen), BlackPixel(self->display, self->screen));
}

static void Graphics_Set_Reverse_Foreground(Graphics *self)
{
	XSetForeground(self->display, DefaultGC(self->display, self->screen), WhitePixel(self->display, self->screen));
}

static void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_Rectangle((Graphics*)data, y, x);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = create_world_with_file(file_name);

	Graphics *graphics = Graphics_Initialize();
	Graphics_Start_Loop(graphics);

	for (;;) {
		Graphics_Set_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		usleep(5000L);

		Graphics_Set_Reverse_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		world = World_Tick(world);
	}

	Graphics_Destroy(graphics);

	return 0;
}

