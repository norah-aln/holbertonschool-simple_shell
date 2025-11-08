#include "shell.h"

/**
 * main - Entry point for simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			break;
		}

		line[_strlen(line) - 1] = '\0'; /* remove \n */
		args = parse_command(line);

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		if (_strcmp(args[0], "exit") == 0)
		{
			free(args);
			break;
		}
		else if (_strcmp(args[0], "env") == 0)
			print_env();
		else
			execute_command(args);

		free(args);
	}

	free(line);
	return (0);
}

