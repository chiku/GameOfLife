#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "main_loop.h"

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

	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	if (!S_ISREG(sb.st_mode) && !S_ISLNK(sb.st_mode)) {
		fprintf(stderr, "'%s' is not a file or a symlink!\n", argv[1]);
		exit(11);
	}

	return argv[1];
}

