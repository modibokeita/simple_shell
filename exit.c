#include "shell.h"

/**
 **_strn_cpy - copies a string
 *@dests: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strn_cpy(char *dests, char *src, int n)
{
	int i, j;
	char *s = dests;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dests[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dests[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strn_cat - concatenates two strings
 *@dests: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strn_cat(char *dests, char *src, int n)
{
	int i, j;
	char *s = dests;

	i = 0;
	j = 0;
	while (dests[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dests[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dests[i] = '\0';
	return (s);
}

/**
 **_str_chr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_str_chr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
