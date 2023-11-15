#include "shell.h"

/**
 * is_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int is_myhistory(info_t *info)
{
	_print_list(info->history);
	return (0);
}

/**
 * _unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _delete_node_at_index(&(info->alias),
		_get_node_index(info->alias, _node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_t *info, char *str)
{
	char *p;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _str_chr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * is_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int is_myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _str_chr(info->argv[i], '=');
		if (p)
			_set_alias(info, info->argv[i]);
		else
			_print_alias(_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
