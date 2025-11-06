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
 * execute_command - executes a command (supports simple args)
 * @command: command to execute (may contain arguments)
 * @argv: argument vector of the shell (used for error prefix)
 */
void execute_command(char *command, char **argv)
{
	pid_t pid;
	int status;
	char *cmd;
	char *token;
	char *args[128];
	int i = 0;
	struct stat st;

	cmd = trim_command(command);

	if (_strlen(cmd) == 0)
		return;

	/* Tokenize command by spaces/tabs into args[] */
	token = strtok(cmd, " \t");
	while (token != NULL && i < 127)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	/* Ensure there is at least a program name */
	if (i == 0)
		return;

	/* Check that the program (as given) exists (we expect a path or ./prog) */
	if (stat(args[0], &st) != 0)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror(argv[0]);
		return;
	}

	if (pid == 0)
	{
		/* Child: execute program with its arguments, pass environ */
		if (execve(args[0], args, environ) == -1)
		{
			perror(argv[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent: wait for the child to finish */
		wait(&status);
	}
}
