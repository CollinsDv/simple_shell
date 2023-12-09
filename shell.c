#include "header.h"

/**
 * main - this is the entry point to my shell
 *
 * Return: EXIT_SUCCESS or FAILURE
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *argv = NULL, **tokens = NULL;
	ssize_t characters = 0;
	size_t size = 0;

	while (1) /* invokes an endless loop for user input */
	{
		prompt(); /* prompt user input */

		characters = getline(&argv, &size, stdin); /* getting user input */

		if (characters < 0)
		{
			perror("getline error");
			free(argv);
			exit(EXIT_FAILURE);
		}
		if (characters == -1) 
			break;
		if (characters == 1 && *argv == '\n')
		{
			free(argv);
			argv = NULL;
			continue;
		}

		tokens = token(argv);
		//printf("in shell(): %s\n", argv);
		execute(tokens, env);

		_free(argv, tokens);
	}
	free(argv);
	exit(EXIT_SUCCESS);
}

/**
 * _free - frees up dynamic memory in main
 * @argv: pointer to user input array
 * @tokens: pointer to tokenized user input
 */
void _free(char *argv, char **tokens)
{
	size_t i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	free(argv);

	argv = NULL;
	tokens = NULL;
}
