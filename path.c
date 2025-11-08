#include "shell.h"

/**
 * find_path - finds full path of a command using PATH
 * @cmd: command name
 * @envp: environment variables
 * Return: string with full path or NULL if not found
 */
char *find_path(char *cmd, char **envp)
{
	int i = 0;
	char *path_env = NULL, *path_copy, *dir;
	char full_path[1024];

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

