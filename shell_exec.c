#include "simple_shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

/**
 * shell_exec - execute program at path with args
 * @s: shell struct
 * @path: program path
 * @args: arguments
 * Return: shell struct or NULL
 */
shell_t *shell_exec(shell_t *s, u8 *path, u8 **args)
{
	pid_t pid;
	int status;
	u8 **envp;
	u64 x;

	if (!s)
		return (0);

	envp = set_consume(set_clone(s->envp));
	if (!envp)
		return (0);

	pid = fork();
	if (pid == -1)
	{
		for (x = 0; envp[x]; x++)
			free(envp[x]);
		free(envp);
		return (0);
	}

	if (pid == 0)
	{
		if (execve((char *)path, (char **)args, (char **)envp) == -1)
		{
			for (x = 0; envp[x]; x++)
				free(envp[x]);
			free(envp);
			return (0);
		}
	}
	else
	{
		wait(&status);
		if (s->exit)
		{
			if (WIFEXITED(status))
				*(s->exit) = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*(s->exit) = 128 + WTERMSIG(status);
		}
	}

	for (x = 0; envp[x]; x++)
		free(envp[x]);
	free(envp);
	return (s);
}

/**
 * run_external - handle external commands via PATH
 * @s: shell struct
 * @args: arguments
 * @line: line number
 * Return: shell struct or NULL
 */
shell_t *run_external(shell_t *s, u8 **args, u64 line)
{
	set_t *set;
	u8 *str;

	s->path->extra = args[0];
	set = set_filter(
		set_add(set_apply(set_clone(s->path), set_apply_path_exec),
		args[0]),
		set_filter_path_exec);
	s->path->extra = 0;

	if (!set)
		return (shell_free(s));

	if (set->size < 1)
	{
		print_not_found(s->name, line + 1, args[0]);
		*(s->exit) = 127;
	}
	else
	{
		str = _strdup(set->data[0]);
		if (!str)
			return (shell_free(s));
		if (!shell_exec(s, str, args))
		{
			print_not_found(s->name, line + 1, args[0]);
			*(s->exit) = 127;
		}
		free(str);
	}
	set_free(set);
	return (s);
}

