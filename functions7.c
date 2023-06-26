#include "main.h"

/**
 * myshell - shell loop
 * @info: cmd info structure
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int myshell(cmdinfo_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		initialize_info(info);
		if (is_interactive(info))
			_puts("$ ");
		write_char(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = get_built_in(info);
			if (builtin_ret == -1)
				get_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	create_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return (builtin_ret);
}

/**
 * get_built_in - finds a builtin command
 * @info: cmd info structure
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int get_built_in(cmdinfo_t *info)
{
	int i, built_in_ret = -1;
	builtin_command_t builtintbl[] = {
		{"exit", _shellexit},
		{"env", _currentenv},
		{"help", _printHelpMessage},
		{"history", _historylist},
		{"setenv", _ssetenv},
		{"unsetenv", _uunsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].command; i++)
		if (_strcmp(info->argv[0], builtintbl[i].command) == 0)
		{
			info->error_count++;
			built_in_ret = builtintbl[i].function(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_command - finds a command in PATH
 * @info: cmd info structure
 * Return: void
 */
void get_command(cmdinfo_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount == 1)
	{
		info->error_count++;
		info->linecount = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_path(info, _getenvvalue(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenvvalue(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - fork
 * @info: cmd info structure
 * Return: void
 */
void fork_command(cmdinfo_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

