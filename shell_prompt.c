#include "simple_shell.h"
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

/**
 * shell_prompt - display shell prompt
 * @s: shell struct
 * Return: shell struct
 */
shell_t *shell_prompt(shell_t *s)
{
	if (!s)
		return (0);
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		print_string(PROMPT_TEXT);
	return (s);
}

/**
 * handle_env_commands - handle built-in env/setenv/unsetenv commands
 * @s: shell struct
 * @args: arguments
 * @line: line number
 * Return: 0 if exit, 1 if continue
 */
int handle_env_commands(shell_t *s, u8 **args, u64 line)
{
	u64 x;

	if (_strlen(args[0]) == _strlen((u8 *)"env") &&
	    _strcmp(args[0], (u8 *)"env") == 0)
	{
		for (x = 0; environ[x]; x++)
		{
			print_string(environ[x]);
			print_char('\n');
		}
		return (1);
	}

	if (_strlen(args[0]) == _strlen((u8 *)"setenv") &&
	    _strcmp(args[0], (u8 *)"setenv") == 0)
	{
		shell_setenv_cmd(s, args);
		return (1);
	}

	if (_strlen(args[0]) == _strlen((u8 *)"unsetenv") &&
	    _strcmp(args[0], (u8 *)"unsetenv") == 0)
	{
		shell_unsetenv_cmd(s, args);
		return (1);
	}

	return (0);
}

