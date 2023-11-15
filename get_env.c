#include "shell.h"

/**
 * _get_environ - returns the string array copy of our environ
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_get_environ(info_t *infos)
{
	if (!infos->environ || infos->env_changed)
	{
		infos->environ = _list_to_strings(infos->env);
		infos->env_changed = 0;
	}

	return (infos->environ);
}

/**
 * is_unsetenv - Remove an environment variable
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @vars: the string env var property
 */
int is_unsetenv(info_t *infos, char *vars)
{
	list_t *node = infos->env;
	size_t i = 0;
	char *p;

	if (!node || !vars)
		return (0);

	while (node)
	{
		p = _starts_with(node->str, vars);
		if (p && *p == '=')
		{
			infos->env_changed = _delete_node_at_index(&(infos->env), i);
			i = 0;
			node = infos->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infos->env_changed);
}

/**
 * is_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @vars: the string env var property
 * @values: the string env var value
 *  Return: Always 0
 */
int is_setenv(info_t *infos, char *vars, char *values)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!vars || !values)
		return (0);

	buf = malloc(_str_len(vars) + _str_len(values) + 2);
	if (!buf)
		return (1);
	_str_cpy(buf, vars);
	_str_cat(buf, "=");
	_str_cat(buf, values);
	node = infos->env;
	while (node)
	{
		p = _starts_with(node->str, vars);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infos->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_node_end(&(infos->env), buf, 0);
	free(buf);
	infos->env_changed = 1;
	return (0);
}
