#include "header.h"

/**
 * path_type - determines if a path is absolute or relative
 * @tokens: tokens containing path
 * @env: environment
 */
char **check_path(char **tokens, char **env)
{
	struct stat st;
	pid_t child;

	if (tokens[0][0] != '/')
		return (tokens);

	if (stat(tokens[0], &st) < 0)
	{
		dprintf(2, "hsh: %s: not found\n", tokens[0]);
		return (NULL);
	}

	child = fork();

	if (child < 0)
	{
		perror("fork error in check_path");
		return (NULL);
	}
	if (child == 0)
	{
		if (execve(tokens[0], tokens, env) == -1)
		{
			perror("execve error in check_path()");
		}
	}
	wait(NULL);
	return (NULL);
}
