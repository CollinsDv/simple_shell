#include "header.h"

/**
 * check_path - determines if a path is absolute or relative
 *
 * @tokens: tokens containing path
 * @env: environment
 * @count: ..
 *
 * Return: pointer to command if it's not an absolute path or NULL
 */
char **check_path(char **tokens, char **env, size_t *count)
{
	struct stat st;
	pid_t child;

	if (tokens[0][0] != '/')
		return (tokens);

	if (stat(tokens[0], &st) < 0)
	{
		dprintf(2, "hsh: [%ld]: %s: not found\n", *count, tokens[0]);
		*count += 1;
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
	*count += 1;
	return (NULL);
}
