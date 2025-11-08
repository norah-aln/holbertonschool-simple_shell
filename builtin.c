#include "shell.h"

/**
 * builtin_exit - handles the exit builtin command
 * @args: arguments
 * Return: 1 if "exit", 0 otherwise
 */
int builtin_exit(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

/**
 * builtin_env - handles the env builtin command
 * @args: arguments
 * @envp: environment variables
 * Return: 1 if "env", 0 otherwise
 */
int builtin_env(char **args, char **envp)
{
	int i;

	if (strcmp(args[0], "env") != 0)
		return (0);

	for (i = 0; envp[i]; i++)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

