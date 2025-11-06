#include "shell.h"

/**
 * is_whitespace - checks if character is whitespace
 * @c: character to check
 *
 * Return: 1 if whitespace, 0 otherwise
 */
int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * skip_spaces - skips leading spaces in string
 * @str: string to process
 *
 * Return: pointer to first non-space character
 */
char *skip_spaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

/**
 * is_empty - checks if string is empty or only whitespace
 * @str: string to check
 *
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *str)
{
	while (*str)
	{
		if (!is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

/**
 * execute_command - executes a command
 * @command: command to execute
 * @argv: argument vector for error messages
 */
void execute_command(char *command, char **argv)
{
	pid_t pid;
	int status;
	char *args[2];
	char *cmd;
	struct stat st;

	cmd = skip_spaces(command);

	if (is_empty(cmd))
		return;

	if (stat(cmd, &st) != 0)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return;
	}

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(argv[0]);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
