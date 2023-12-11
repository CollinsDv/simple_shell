#ifndef HEADER
#define HEADER

#define BUFFER 1024
/*
 * header files
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * user defined functions
 */
size_t _strlen(char *s);
char **token(char *str);
void print(char *str);
size_t _strlen(char *str);
void prompt(void);
void execute(char *tokens[], char **env, size_t *count);
void _free(char *argv, char **tokens);
char *_getenv(char *enviroment, char **env, size_t *count);
void free_path(char **dup_path);
char **command_path(char **token, char *environ_path, size_t *count);
char **check_path(char **tokens, char **env, size_t *count);

#endif
