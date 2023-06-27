#include "main.h"

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
		chdir_ret =
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
