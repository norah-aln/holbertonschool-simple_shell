#include "simple_shell.h"
#include <stdlib.h>

/**
 * shell_iter_line - handle a single command line
 * @s: shell struct
 * @args: arguments
 * @line: line number
 * Return: shell struct or NULL
 */
shell_t *shell_iter_line(shell_t *s, u8 **args, u64 line)
{
	u64 x, y;
	u8 **a;
	u8 f;

	if (!s || !args)
		return (shell_free(s));
	if (!args[0])
		return (s);

	if (shell_exit_cmd(s, args) == 0)
		return (0);

	if (handle_env_commands(s, args, line))
		return (s);

	f = 0;
	a = _strsplit(args[0], (u8 *)" ");
	if (!a)
		return (shell_free(s));

	s = run_external(s, a, line);

	for (y = 0; a[y]; y++)
		free(a[y]);
	free(a);

	if (f)
		return (0);
	return (s);
}

/**
 * shell_iter - main loop over commands
 * @s: shell struct
 * Return: shell struct or NULL
 */
shell_t *shell_iter(shell_t *s)
{
	u8 **l;
	u64 x;
	u8 f;
	char *norm;
	u8 **a;

	if (!s)
		return (0);

	l = _strsplit(read_line(), (u8 *)";\n");
	if (!l)
		return (shell_exit(s, 1));

	f = 0;
	for (x = 0; l[x]; x++)
	{
		a = _strsplit(l[x], (u8 *)" ");
		if (!a)
			continue;

		f = (shell_iter_line(s, a, x) == 0);

		for (u64 y = 0; a[y]; y++)
			free(a[y]);
		free(a);

		if (f)
			break;
	}

	for (x = 0; l[x]; x++)
		free(l[x]);
	free(l);

	if (f)
		return (0);
	return (s);
}

/**
 * shell_runtime - entry loop
 * @s: shell struct
 * Return: shell struct
 */
shell_t *shell_runtime(shell_t *s)
{
	if (!s)
		return (0);

	shell_set_signal();

	while (1)
		if (!shell_iter(shell_prompt(s)))
			return (0);

	return (shell_free(s));
}

