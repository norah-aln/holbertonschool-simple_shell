#include "shell.h"

/**
 * _strlen - return length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	while (s && s[i])
		i++;
	return (i);
}

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 * Return: difference between characters
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strdup - duplicate a string
 * @str: input string
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	int len = _strlen(str);
	char *dup = malloc(len + 1);
	int i;

	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

/**
 * _strcpy - copy a string
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;

	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

