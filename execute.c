#include "shell.h"

/**
 * is_space - checks if character is space or tab
 * @c: character to check
 *
 * Return: 1 if space, 0 otherwise
 */
int is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * trim_command - removes leading and trailing spaces from command
 * @cmd: command string
 *
 * Return: pointer to trimmed string
 */
char *trim_command(char *cmd)
{
	char *end;

	while (is_space(*cmd))
		cmd++;

	if (*cmd == '\0')
		return (cmd);

	end = cmd + _strlen(cmd) - 1;
	while (end > cmd && is_space(*end))
	{
		*end = '\0';
		end--;
	}

	return (cmd);
}

/**
 * execute_command - executes a command
 * @command: command to execute
 * @argv: argument vector
 */
void execute_command(char *command, char **argv)
{
	pid_t pid;
	int status;
	char *args[2];
	char *cmd;
	struct stat st;

	cmd = trim_command(command);

	if (_strlen(cmd) == 0)
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
