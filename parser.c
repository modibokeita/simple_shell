#include "shell.h"

/**
 * command - determines if a file is an executable command
 * @infos: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int command(info_t *infos, char *path)
{
	struct stat st;

	(void)infos;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * is_dup_chars - duplicates characters
 * @path_str: the PATH string
 * @starts: starting index
 * @stops: stopping index
 *
 * Return: pointer to new buffer
 */
char *is_dup_chars(char *path_str, int starts, int stops)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = starts; i < stops; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _find_path - finds this cmd in the PATH string
 * @infos: the info struct
 * @path_str: the PATH string
 * @cmmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_find_path(info_t *infos, char *path_str, char *cmmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_str_len(cmmd) > 2) && _starts_with(cmmd, "./"))
	{
		if (command(infos, cmmd))
			return (cmmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = is_dup_chars(path_str, curr_pos, i);
			if (!*path)
				_str_cat(path, cmmd);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, cmmd);
			}
			if (command(infos, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
