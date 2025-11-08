#include "shell.h"

/**
 * execute_cmd - executes a command by creating child process
 * @cmd_path: full path of command
 * @args: arguments
 * @envp: environment variables
 */
void execute_cmd(char *cmd_path, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

