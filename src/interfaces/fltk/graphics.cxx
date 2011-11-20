#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "graphics.h"

Graphics::Graphics()
{
	window = new Fl_Double_Window(SCREEN, SCREEN, "Conway's Game of Life");
	orange = fl_rgb_color(200, 100, 50);

	window->end();
	window->show();
	Fl::wait();
}

Graphics::~Graphics()
{
	window->clear();
}

void Graphics::Draw_Square(long int x, long int y)
{
	Fl_Box *box = new Fl_Box(
		SCREEN/2 + x * SQUARE,
		SCREEN/2 + y * SQUARE,
		SQUARE - 1, SQUARE - 1,
		""
	);
	box->box(FL_FLAT_BOX);
	box->color(orange);
	window->add(box);
}

void Graphics::Flush()
{
	Fl::flush();
}

void Graphics::Clear()
{
	window->clear();
}

void Graphics::Redraw()
{
	window->redraw();
}

