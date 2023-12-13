#include "header.h"

/**
 * execute - handles process executions of commands-line arguements
 *
 * @token: pointer to the tokens
 * @env: pointer to environment
 * @count: pointer to count in main
 */
void execute(char *token[], char **env, size_t *count)
{
	pid_t child;
	ssize_t exec_val;
	char *environment = NULL, **environ_path = NULL;

	if (check_path(token, env, count) == NULL)
	{
		return;
	}
	environment = _getenv("PATH", env, count);
	if (environment == NULL)
	{
		perror("PATH not found");
		return;
	}
	environ_path = command_path(token, environment, count);
	if (environ_path == NULL)
		return;

	child = fork();

	if (child < 0)
	{
		perror("fork error in execute()");
		exit(EXIT_FAILURE);
	}
	if (child == 0)
	{
		exec_val = execve(environ_path[0], token, env);
		if (exec_val < 0)
		{
			perror("execve error in execute()");
		}
	}
	else
	{
		wait(NULL);
		free_path(environ_path);
		*count += 1;
	}
}

/**
 * _getenv - gets the environment PATH
 *
 * @environment: string containing PATH string
 * @env: environment variables
 * @count: pointer to count in main
 *
 * Return: pointer to PATH environment from env
 */
char *_getenv(char *environment, char **env, size_t *count)
{
	size_t i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], environment, strlen(environment)) == 0)
			return (env[i]);
		i++;
	}
	*count += 1;
	return (NULL);
}

/**
 * command_path - establishes a new command path of the command input
 *
 * @token: command table with the command in token[1]
 * @environ_path: system path
 * @count: pointer to count in main
 *
 * Return: new path with command appended to system directories
 */
char **command_path(char **token, char *environ_path, size_t *count)
{
	struct stat st;
	size_t buffer = 2, position; /* (2) - including the null terminator */
	char *path = NULL, **new_path = NULL, *environ_copy = NULL;

	new_path = malloc(sizeof(*new_path) * buffer);
	if (new_path == NULL)
	{
		perror("malloc error in command_path");
		exit(EXIT_FAILURE);
	}
	environ_copy = strdup(environ_path);
	path = strtok(environ_copy, ":");
	position = 0;
	while (path != NULL)
	{
		new_path[position] = malloc(strlen(path) + 1 + strlen(token[0]) + 1);
		if (new_path[position] == NULL)
		{
			perror("malloc error in command_path");
			exit(EXIT_FAILURE);
		}
		strcpy(new_path[position], path);
		strcat(new_path[position], "/");
		strcat(new_path[position], token[0]);

		if (stat(new_path[position], &st) == 0)
		{
			free(environ_copy);
			new_path[position + 1] = NULL; /* Null-terminate the array */
			return (new_path);
		}
		free(new_path[position]);
		path = strtok(NULL, ":");
	}
	free(environ_copy);
	new_path[position + 1] = NULL;
	free_new_path(new_path);
	dprintf(2, "hsh: [%ld]: %s: doesn't exist\n", *count, token[0]);
	*count += 1;
	return (NULL);
}

/**
 * free_path - frees memory location for dynamic memory
 *
 * @dup_path: path to free
 */
void free_path(char **dup_path)
{
	size_t i;

	for (i = 0; dup_path[i] != NULL; i++)
		free(dup_path[i]);
	free(dup_path);
	dup_path = NULL;
}

/**
 * free_new_path - handles malloc reallocation in command_path
 *                 if command isn't found
 *
 * @new_path: path to malloc
 */
void free_new_path(char **new_path)
{
	size_t i;

	for (i = 1; new_path[i] != NULL; i++)
		free(new_path[i]);
	free(new_path);
	new_path = NULL;
}
