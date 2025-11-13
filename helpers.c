#include "shell.h"

/* Simple reimplementations of some string functions */

int _strlen(char *s)
{
    int i = 0;
    while (s && s[i])
        i++;
    return (i);
}

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

/* إضافة _strchr حتى تعمل _strsplit */
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

