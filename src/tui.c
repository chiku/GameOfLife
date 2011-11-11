#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>

#include <game_of_life.h>

static void usage(char *exec_file_name)
{
	printf("Usage: \n\t%s <file name>\n\t%s --help (-h)\n", exec_file_name, exec_file_name);
}

static void handle_signal_for(char *message, int exit_status)
{
	curs_set(1);
	endwin();
	printf(message);
	exit(exit_status);
}

static void catch_sigint(int sig_num)
{
	handle_signal_for("SIGINT received!\n", 0);
}

static void catch_sigterm(int sig_num)
{
	handle_signal_for("SIGTERM received!\n", 0);
}

static void catch_sigkill(int sig_num)
{
	handle_signal_for("SIGKILL received!\n", 1);
}

static World* create_world_with_file(char *file_name)
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("File %s doesn't exist\n", file_name);
		exit(11);
	}

	World *world = World_Initialize();
	Cell *cell;
	long int x, y, i, count;
	while (fscanf(fp, "%ld %ld", &x, &y) != EOF)
		Cell_Initialize(world, x, y);
	fclose(fp);

	return world;
}

static void print_cell(long int x, long int y)
{
	mvprintw(y + LINES/2, x + COLS/2, "X");
}

int main(int argc, char *argv[])
{
	char *exec_name = argv[0];

	if (argc <= 1 || argv[1][0] == '\0') {
		usage(exec_name);
		return 10;
	}

	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		usage(exec_name);
		return 0;
	}

	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigterm);
	signal(SIGKILL, catch_sigkill);

	World *world = create_world_with_file(argv[1]);
	long int i, count;
	Cell *cell;

	initscr();
	noecho();
	curs_set(0);

	for (;;) {
		World_At_Each_Cell(world, print_cell);
		refresh();
		usleep(500000L);
		erase();
		world = World_Tick(world);
	}
	endwin();

	return 0;
}

