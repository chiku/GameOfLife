#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <game_of_life.h>

static void usage(char *exec_file_name)
{
	printf("Usage: \n\t%s <file name>\n\t%s --help (-h)\n", exec_file_name, exec_file_name);
}

char *handle_command_line_arguments(int argc, char *argv[])
{
	char *exec_name = argv[0];

	if (argc <= 1 || argv[1][0] == '\0') {
		usage(exec_name);
		exit(10);
	}

	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		usage(exec_name);
		exit(0);
	}

	return argv[1];
}

World* create_world_with_file(char *file_name)
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("File %s doesn't exist\n", file_name);
		exit(11);
	}

	World *world = World_Initialize();
	long int x, y;
	while (fscanf(fp, "%ld %ld", &x, &y) != EOF)
		Cell_Initialize(world, x, y);
	fclose(fp);

	return world;
}

