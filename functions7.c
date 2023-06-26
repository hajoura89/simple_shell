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
 * is_command - checks if command
 * @info: cmd info structure
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_command(cmdinfo_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: start index
 * @stop: stop index
 * Return: pointer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * get_path - get path
 * @info: cmd info structure
 * @pathstr: PATH string
 * @cmd: cmd to find
 * Return: path of cmd or NULL
 */
char *get_path(cmdinfo_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
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
