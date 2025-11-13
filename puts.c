#include <unistd.h>

/**
 * _puts - prints a string to stdout
 * @s: string to print
 */
void _puts(char *s)
{
	while (*s)
		write(1, s++, 1);
}

