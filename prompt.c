#include "header.h"

/**
 * prompt - displays a prompt for user entry
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
}
