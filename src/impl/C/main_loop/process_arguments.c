#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "main_loop/main_loop.h"

static void usage(char *exec_file_name)
{
	printf("Usage: \n\t%s [file name]\n\t%s [file name] [optional delay in ms]\n\t%s --help (-h)\n", exec_file_name, exec_file_name, exec_file_name);
}

char *file_name_on_valid_command_line_arguments(int argc, char *argv[])
{
	char *exec_name = argv[0], *first_arg = argv[1];

	if (argc <= 1 || first_arg[0] == '\0') {
		usage(exec_name);
		exit(10);
	}

	if (strcmp(first_arg, "--help") == 0 || strcmp(first_arg, "-h") == 0) {
		usage(exec_name);
		exit(0);
	}

	struct stat sb;
	if (stat(first_arg, &sb) == -1) {
		perror(first_arg);
		exit(EXIT_FAILURE);
	}

	if (!S_ISREG(sb.st_mode) && !S_ISLNK(sb.st_mode)) {
		fprintf(stderr, "'%s' is not a file or a symlink!\n", first_arg);
		exit(11);
	}

	return first_arg;
}

long int delay_time_on_presence_in_command_line_arguments(int argc, char *argv[])
{
	char *second_arg = argv[2];
	long int delay_time = 100;

	if (argc <= 2 || second_arg[0] == '\0') {
		return delay_time;
	}

	delay_time = atol(second_arg);
	delay_time = delay_time < 10 ? 10 : delay_time;
	return delay_time;
}
