#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "main_loop.h"

static void catch_sigint(int sig_num)
{
	cleanup_on_signal();
	fprintf(stdout, "SIGINT received!\n");
	exit(0);
}

static void catch_sigterm(int sig_num)
{
	cleanup_on_signal();
	fprintf(stdout, "SIGTERM received!\n");
	exit(0);
}

static void catch_sigkill(int sig_num)
{
	cleanup_on_signal();
	fprintf(stdout, "SIGKILL received!\n");
	exit(1);
}

void initialize_signal_handlers(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigterm);
	signal(SIGKILL, catch_sigkill);
}
