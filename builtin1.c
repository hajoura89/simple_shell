#include "main.h"

/**
 * _shellexit - exits the shell
 * @info: cmd info structure
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _shellexit(cmdinfo_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = parse_integer(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			print_input_string(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->error_code = parse_integer(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}

/**
 * _cd - changes the current directory
 * @info: cmd info structure
 * Return: Always 0
 */
int _cd(cmdinfo_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("failure msg \n");
	if (!info->argv[1])
	{
		dir = _getenvvalue(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenvvalue(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenvvalue(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenvvalue(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenvvalue(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cannot cd to ");
		print_input_string(info->argv[1]), write_char('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenvvalue(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _printHelpMessage - display a help message
 * @info: cmd info structure
 * Return: Always 0
 */
int _printHelpMessage(cmdinfo_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

