#include "header.h"

/**
 * execute - handles process executions of commands-line arguements
 *
 * @token: pointer to the tokens
 */
void execute(char *token[], char **env)
{
	pid_t child;
	ssize_t exec_val;
	char *environment = NULL, **environ_path = NULL;

	environment = _getenv("PATH", env);
	if (environment == NULL)
	{
		perror("PATH not found");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", environment);

	environ_path = command_path(token, environment);
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
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free_path(environ_path);
		printf("i am free\n");
	}
}

/**
 * _getenv - gets the environment PATH
 * 
 * @environment: string containing PATH string
 * @env: environment variables
 *
 * Return: pointer to PATH environment from env
 */
char *_getenv(char *environment, char **env)
{
	size_t i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], environment, strlen(environment)) == 0)
			return (env[i]);
		else
			i++;
	}

	return (env[i]);
}

/**
 * command_path - establishes a new command path of the command input
 *
 * @token: command table with the command in token[1]
 * @environ_path: system path
 *
 * Return: new path with command appended to system directories
 */
char **command_path(char **token, char *environ_path)
{
	struct stat st;
	char *path = NULL, **new_path = NULL, *environ_copy = NULL;
	size_t buffer = 2; /* Initial buffer size, including the null terminator */


	new_path = malloc(sizeof(*new_path) * buffer);
	if (new_path == NULL)
	{
		perror("malloc error in command_path");
		exit(EXIT_FAILURE);
	}

	environ_copy = strdup(environ_path);
	path = strtok(environ_copy, ":");

	size_t position = 0;
	while (path != NULL)
	{
		if (position >= buffer - 1) /* Check if we need to resize the array */
		{
			buffer *= 2; /* Double the buffer size */
			new_path = realloc(new_path, sizeof(*new_path) * buffer);
			if (new_path == NULL)
			{
				perror("realloc error in command_path()");
				exit(EXIT_FAILURE);
			}
		}

		new_path[position] = malloc(strlen(path) + 1 + strlen(token[0]) + 1);
		if (new_path[position] == NULL)
		{
			perror("malloc error in command_path");
			exit(EXIT_FAILURE);
		}

		strcpy(new_path[position], path);
		strcat(new_path[position], "/");
		strcat(new_path[position], token[0]);
		strcat(new_path[position], "\0");

		printf("%s\n", new_path[position]);

		if (stat(new_path[position], &st) == 0)
		{
			printf("PATH found\n");
			free(environ_copy);
			new_path[position + 1] = NULL; // Null-terminate the array
			printf("before return: %s\n", new_path[position]);
			return (new_path);
		}
		printf("%s not found\n", new_path[position]);

		free(new_path[position]);
		//position++;
		path = strtok(NULL, ":");
	}

	free(environ_copy);
	dprintf(2, "%s: command doesn't exist\n", token[0]);
	return (NULL);
}

/**
 * free_path - frees memory location for new command path
 *
 * @path: command path
 */
void free_path(char **dup_path)
{
	//size_t i;

	//for (i = 0; dup_path[i] != NULL; i++)
	//	free(dup_path[i]);
	free(dup_path);
	dup_path = NULL;
}
