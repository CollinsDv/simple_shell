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
	size_t buffer = BUFFER, position, length;
	char *token = NULL, **tokens = NULL, *new_str = NULL;

	new_str = strdup(str);
	length = strlen(new_str);
	if (length > 0 && new_str[length - 1] == '\n')
		new_str[length - 1] = '\0';

	tokens = malloc(buffer * sizeof(*tokens));
	if (tokens == NULL)
	{
		perror("hsh");
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
		/* printf("size: %ld\n", strlen(token)); */
		/* printf("token: %s\n", token); */
		if (strlen(token) > 0) /* skip empty token */
			tokens[position] = strdup(token);
		/* printf("dup: %s\n", tokens[position]);*/
		position++;
		token = strtok(NULL, " ");
	}
	tokens[position] = NULL;  /* Null-terminate the array */
	free(new_str);
	return (tokens);
}
