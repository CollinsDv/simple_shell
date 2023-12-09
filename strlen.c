#include "header.h"

/**
 * _strlen - Returns the length of a string
 * @s: String to count
 *
 * Return: String length
 */
size_t _strlen(char *s)
{
	size_t c = 0;

	while (*s)
	{
		c++;
	}

	return (c);
}
