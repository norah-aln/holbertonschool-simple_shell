#include "shell.h"

/**
 * execute_command - executes a command
 * @command: command to execute
 * @program_name: name of the program (for error messages)
 */
void execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char *args[2];
	struct stat st;

	if (command == NULL || _strlen(command) == 0)
		return;

	if (stat(command, &st) != 0)
	{
		write(STDERR_FILENO, program_name, _strlen(program_name));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return;
	}

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror(program_name);
		return;
	}

	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror(program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
