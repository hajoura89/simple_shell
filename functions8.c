#include "main.h"

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

