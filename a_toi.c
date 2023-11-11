#include "shell.h"

/**
 * mode_interactive - returns true if shell is interactive mode
 * @infos: gets infos from address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int mode_interactive(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * is_a_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_a_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_is_alpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_a_toi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _a_toi(char *str)
{
	int i, signs = 1, flags = 0, outputs;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flags != 2; i++)
	{
		if (str[i] == '-')
			signs *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		outputs = -result;
	else
		outputs = result;

	return (outputs);
}
