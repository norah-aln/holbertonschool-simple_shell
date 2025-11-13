#include "simple_shell.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

/**
 * get_cd_target - determine target directory for "cd"
 * @args: argument list
 *
 * Return: pointer to target path or NULL
 */
char *get_cd_target(u8 **args)
{
	if (args[1] == NULL)
		return (_getenv("HOME"));

	if (_strcmp(args[1], (u8 *)"-") == 0)
		return (_getenv("OLDPWD"));

	return ((char *)args[1]);
}

/**
 * shell_cd_cmd - builtin "cd" command
 * @s: pointer to shell_t struct
 * @args: argument list
 *
 * Return: pointer to shell_t struct
 */
shell_t *shell_cd_cmd(shell_t *s, u8 **args)
{
	char cwd[PATH_MAX];
	char *target = NULL;
	int rc;

	if (!s || !args || !args[0])
		return (s);

	if (_strcmp(args[0], (u8 *)"cd") != 0)
		return (s);

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';

	target = get_cd_target(args);

	if (target == NULL)
	{
		_puts("cd: target not found\n");
		return (s);
	}

	rc = chdir(target);
	if (rc == -1)
	{
		perror("cd");
	}
	else
	{
		_setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			_setenv("PWD", cwd, 1);
	}

	return (s);
}

