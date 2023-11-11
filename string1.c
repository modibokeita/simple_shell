#include "shell.h"

/**
 * _str_cpy - copies a string
 * @dests: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_str_cpy(char *dests, char *src)
{
	int i = 0;

	if (dests == src || src == 0)
		return (dests);
	while (src[i])
	{
		dests[i] = src[i];
		i++;
	}
	dests[i] = 0;
	return (dests);
}

/**
 * _str_dup - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_str_dup(const char *s)
{
	int length = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--s;
	return (ret);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

