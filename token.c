#include "header.h"

/**
 * token - tokenizes a string by removing delimiters
 *
 * @str: string to be tokenized
 *
 * Return: pointer to tokenized array
 */
char **token(char *str)
{
	char *token = NULL, **tokens = NULL, *new_str = NULL;
	size_t buffer = BUFFER, position, length;
	
	new_str = strdup(str);

	length = strlen(new_str);
	if (length > 0 && new_str[length - 1] == '\n')
		new_str[length - 1] = '\0';

	tokens = malloc(buffer * sizeof(*tokens));
	if (tokens == NULL)
	{
		perror("malloc error in token function");
		exit(EXIT_FAILURE);
	}

	token = strtok(new_str, " ");
	position = 0;
	while (token != NULL)
	{
		if (position >= (buffer - 1)) /* buffer is full, realloc space */
		{
			buffer += BUFFER;
			tokens = realloc(tokens, sizeof(*tokens) * buffer);
			if (tokens == NULL)
			{
				perror("realloc error in token function");
				exit(EXIT_FAILURE);
			}
		}
		if (strlen(token) > 0) /* skip empty token */
			tokens[position] = token;
		position++;
		strtok(NULL, " ");
	}
	tokens[position] = NULL;  /* Null-terminate the array */
	free(new_str);
	return (tokens);
}
