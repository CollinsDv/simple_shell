#include "header.h"

/**
 * main - this is the entry point to my shell
 *
 * @ac: unused arguement count
 * @av:  unused arguement vector
 * @env: environment variable
 *
 * Return: EXIT_SUCCESS or FAILURE
 */
int main(int ac, char **av, char **env)
{
	char *argv = NULL, **tokens = NULL;
	ssize_t characters = 0;
	size_t size = 0, count = 1;
	(void)ac;
	(void)av;

	while (1) /* invokes an endless loop for user input */
	{
		prompt(); /* prompt user input */

		characters = getline(&argv, &size, stdin); /* getting user input */
		if (characters < 0)
		{
			free(argv);
			argv = NULL;
			exit(EXIT_SUCCESS);
		}
		if (characters == 1 && *argv == '\n')
		{
			free(argv);
			argv = NULL;
			count++;
			continue;
		}
		tokens = token(argv);
		if (tokens[0] == NULL)
		{
			_free(argv, tokens);
			continue;
		}
		if (strcmp(tokens[0], "exit") == 0 || strcmp(tokens[0], "quit") == 0)
		{
			free(argv);
			_free(argv, tokens);
			exit(EXIT_SUCCESS);
		}
		execute(tokens, env, &count);
		_free(argv, tokens);
	}
}

/**
 * _free - frees up dynamic memory in main
 * @argv: pointer to user input array
 * @tokens: pointer to tokenized user input
 */
void _free(char *argv, char **tokens)
{
	size_t i;
	(void)argv;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	/* free(argv); */

	argv = NULL;
	tokens = NULL;
}
