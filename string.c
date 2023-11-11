#include "shell.h"

/**
 * _str_len - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _str_comp - performs lexicogarphic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive
 */
int _str_comp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _starts_with - checks if needle starts with haystack
 * @haystacks: string to search
 * @needles: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *_starts_with(const char *haystacks, const char *needles)
{
	while (*needles)
		if (*needles++ != *haystacks++)
			return (NULL);
	return ((char *)haystacks);
}

/**
 * _str_cat - concatenates two strings
 * @dests: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_str_cat(char *dests, char *src)
{
	char *ret = dests;

	while (*dests)
		dests++;
	while (*src)
		*dests++ = *src++;
	*dests = *src;
	return (ret);
}
