#include "shell.h"

/**
 * trim_whitespace - removes leading and trailing whitespace
 * @str: string to trim
 *
 * Return: pointer to trimmed string
 */
char *trim_whitespace(char *str)
{
	char *end;

	if (str == NULL)
		return (NULL);

	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0)
		return (str);

	end = str + _strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	*(end + 1) = '\0';

	return (str);
}

/**
 * is_empty_line - checks if line is empty or contains only whitespace
 * @str: string to check
 *
 * Return: 1 if empty, 0 otherwise
 */
int is_empty_line(char *str)
{
	int i = 0;

	if (str == NULL)
		return (1);

	while (str[i])
	{
		if (!isspace((unsigned char)str[i]))
			return (0);
		i++;
	}

	return (1);
}
