#include "main.h"

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
/**
 * _historylist - displays the history list
 * @info: cmd info structure
 * Return: Always 0
 */
int _historylist(cmdinfo_t *info)
{
	print_list(info->history);
	return (0);
}
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
