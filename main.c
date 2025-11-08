#include "shell.h"

/**
 * main - Entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: Always 0
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL, *cmd_path = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = tokenize_line(line);
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		if (builtin_exit(args))
		{
			free_args(args);
			break;
		}
		if (builtin_env(args, envp))
		{
			free_args(args);
			continue;
		}

		cmd_path = find_path(args[0], envp);
		if (!cmd_path)
		{
			perror(args[0]);
			free_args(args);
			continue;
		}

		execute_cmd(cmd_path, args, envp);
		free(cmd_path);
		free_args(args);
	}
	free(line);
	return (0);
}

