#include <FL/Fl_Double_Window.H>

#include "fltk/canvas.hh"
#include "fltk/window.hh"

GameOfLife::FLTK::Window::Window(GameOfLife::Game *game)
{
	window = new Fl_Double_Window(1280, 800);
	window->fullscreen();
	window->label("Conway's Game of life");

	canvas = new GameOfLife::FLTK::Canvas(game, WIDTH, HEIGHT);
	window->add(canvas);
	window->end();
}

GameOfLife::FLTK::Window::~Window()
{
	delete window;
}

void GameOfLife::FLTK::Window::show()
{
	window->show();
}

