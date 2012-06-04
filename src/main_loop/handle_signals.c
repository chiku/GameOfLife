#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "main_loop.h"

static void handle_signal_for(const char *message, int exit_status)
{
	cleanup_on_signal();
	fprintf((exit_status ? stderr : stdout), message);
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

void initialize_signal_handlers(void)
{
	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigterm);
	signal(SIGKILL, catch_sigkill);
}

