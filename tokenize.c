#include "shell.h"

/**
 * tokenize_line - splits a line into tokens
 * @line: input string
 * Return: pointer to array of tokens
 */
char **tokenize_line(char *line)
{
	char *token;
	char **args;
	int bufsize = 64, i = 0;

	args = malloc(bufsize * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(line, " \t\r\n");
	while (token)
	{
		args[i] = strdup(token);
		i++;
		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, bufsize * sizeof(char *));
			if (!args)
			{
				perror("realloc");
				return (NULL);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;
	return (args);
}

/**
 * free_args - frees memory for array of strings
 * @args: array of arguments
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

