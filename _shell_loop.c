#include "shell.h"

/**
 * _hsh - main shell loop
 * @infos: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *infos, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clear_info(infos);
		if (mode_interactive(infos))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = _get_input(infos);
		if (r != -1)
		{
			_set_info(infos, argv);
			builtin_ret = _find_builtin(infos);
			if (builtin_ret == -1)
				_find_command(infos);
		}
		else if (mode_interactive(infos))
			_putchar('\n');
		_free_info(infos, 0);
	}
	_write_history(infos);
	_free_info(infos, 1);
	if (!mode_interactive(infos) && infos->status)
		exit(infos->status);
	if (builtin_ret == -2)
	{
		if (infos->err_num == -1)
			exit(infos->status);
		exit(infos->err_num);
	}
	return (builtin_ret);
}

/**
 * _find_builtin - finds a builtin command
 * @infos: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _find_builtin(info_t *infos)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", is_myexit},
		{"env", is_myenv},
		{"help", is_myhelp},
		{"history", is_myhistory},
		{"setenv", is_mysetenv},
		{"unsetenv", is_myunsetenv},
		{"cd", is_mycd},
		{"alias", is_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_comp(infos->argv[0], builtintbl[i].type) == 0)
		{
			infos->line_count++;
			built_in_ret = builtintbl[i].func(infos);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_command - finds a command in PATH
 * @infos: the parameter & return info struct
 *
 * Return: void
 */
void _find_command(info_t *infos)
{
	char *path = NULL;
	int i, k;

	infos->path = infos->argv[0];
	if (infos->linecount_flag == 1)
	{
		infos->line_count++;
		infos->linecount_flag = 0;
	}
	for (i = 0, k = 0; infos->arg[i]; i++)
		if (!is_a_delim(infos->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _find_path(infos, is_getenv(infos, "PATH="), infos->argv[0]);
	if (path)
	{
		infos->path = path;
		_fork_command(infos);
	}
	else
	{
		if ((mode_interactive(infos) || is_getenv(infos, "PATH=")
			|| infos->argv[0][0] == '/') && command(infos, infos->argv[0]))
			_fork_command(infos);
		else if (*(infos->arg) != '\n')
		{
			infos->status = 127;
			_print_error(infos, "not found\n");
		}
	}
}

/**
 * _fork_command - forks a an exec thread to run cmd
 * @infos: the parameter & return info struct
 *
 * Return: void
 */
void _fork_command(info_t *infos)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infos->path, infos->argv, _get_environ(infos)) == -1)
		{
			_free_info(infos, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infos->status));
		if (WIFEXITED(infos->status))
		{
			infos->status = WEXITSTATUS(infos->status);
			if (infos->status == 126)
				_print_error(infos, "Permission denied\n");
		}
	}
}
