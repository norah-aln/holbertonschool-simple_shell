#include "shell.h"

/**
 * _strchr - locate character in string
 * @s: string
 * @c: character to find
 * Return: pointer to first occurrence or NULL
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	if (!s)
		return (NULL);

	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}

	if (s[i] == c)
		return (s + i);
	return (NULL);
}

