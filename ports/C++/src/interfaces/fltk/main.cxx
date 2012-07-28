#include <iostream>
#include <string>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "game.hh"
#include "fltk/window.hh"
#include "fltk/runner.hh"

static const void usage(std::string exec_file_name)
{
	std::cout << "Usage: " << std::endl
	             << "\t" << exec_file_name << " <file name>" << std::endl
	             << "\t" << exec_file_name << " --help (-h)" << std::endl;
}

static const std::string handle_command_line_arguments(int argc, char *argv[])
{
	std::string exec_name(argv[0]);

	if (argc <= 1 || argv[1][0] == '\0') {
		usage(exec_name);
		exit(10);
	}

	std::string first_arg(argv[1]);
	if (first_arg == "--help" || first_arg == "-h") {
		usage(exec_name);
		exit(0);
	}

	struct stat sb;
	if (stat(first_arg.c_str(), &sb) == -1) {
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!S_ISREG(sb.st_mode) && !S_ISLNK(sb.st_mode)) {
		std::cerr << "\'" << first_arg << "' is not a file or a symlink!" << std::endl;
		exit(11);
	}

	return first_arg;
}


int main(int argc, char *argv[])
{
	std::string file_name = handle_command_line_arguments(argc, argv);
	GameOfLife::Game *game = new GameOfLife::Game();
	game->read(file_name);

	GameOfLife::FLTK::Window *window = new GameOfLife::FLTK::Window();

	GameOfLife::FLTK::Runner runner(game, window);
	return runner.init();
}
