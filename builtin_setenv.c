#include "simple_shell.h"

/**
 * validate_name_value - validate env name and value
 * @name: variable name
 * @value: variable value
 * Return: 0 if valid, -1 if invalid
 */
int validate_name_value(const char *name, const char *value)
{
	size_t i;

	if (!name || !*name || !value)
		return (-1);

	for (i = 0; name[i]; i++)
		if (name[i] == '=')
			return (-1);

	return (0);
}

/**
 * _build_nv - build NAME=VALUE string
 * @name: variable name
 * @value: variable value
 * Return: new string or NULL on failure
 */
char *_build_nv(const char *name, const char *value)
{
	size_t ln = _strlen_local(name);
	size_t lv = _strlen_local(value);
	size_t i;
	char *s = malloc(ln + 1 + lv + 1);

	if (!s)
		return (NULL);

	for (i = 0; i < ln; i++)
		s[i] = name[i];
	s[ln] = '=';
	for (i = 0; i < lv; i++)
		s[ln + 1 + i] = value[i];
	s[ln + 1 + lv] = '\0';

	return (s);
}

/**
 * update_existing_env - update an existing environment variable
 * @name: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int update_existing_env(const char *name, const char *value)
{
	size_t i, nlen;
	char *nv;

	nlen = _strlen_local(name);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp_local(environ[i], name, nlen) == 0 &&
		    environ[i][nlen] == '=')
		{
			nv = _build_nv(name, value);
			if (!nv)
				return (-1);

			free(environ[i]);
			environ[i] = nv;
			return (0);
		}
	}

	return (-1);
}

/**
 * add_new_env - add a new environment variable
 * @name: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int add_new_env(const char *name, const char *value)
{
	size_t count = 0, j;
	char *nv;
	char **newenv;

	for (count = 0; environ[count]; count++)
		;

	newenv = malloc(sizeof(char *) * (count + 2));
	if (!newenv)
		return (-1);

	for (j = 0; j < count; j++)
		newenv[j] = environ[j];

	nv = _build_nv(name, value);
	if (!nv)
	{
		free(newenv);
		return (-1);
	}

	newenv[count] = nv;
	newenv[count + 1] = NULL;

	free(environ);
	environ = newenv;

	return (0);
}

/**
 * _setenv - set or replace an environment variable
 * @name: variable name (no '=')
 * @value: variable value
 * @overwrite: 0 = keep existing, 1 = replace
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int ret;

	if (validate_name_value(name, value) == -1)
		return (-1);

	ret = update_existing_env(name, value);
	if (ret == 0)
		return (overwrite ? update_existing_env(name, value) : 0);

	return (add_new_env(name, value));
}

