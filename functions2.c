#include "main.h"

/**
 * initialize_info - initializes info struct
 * @info: cmd info structure
 */
void initialize_info(cmdinfo_t *info)
{
	/* Set all fields of the info struct to their default values */
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - initializes info struct
 * @info: cmd info structure
 * @av: argument vector
 */
void set_info(cmdinfo_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = _split_str(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strduplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
		{
			/* Empty loop body */
		}
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - frees info struct fields
 * @info: cmd info structure
 * @all: true if freeing all fields
 */
void free_info(cmdinfo_t *info, int all)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->enviro)
			free_list(&(info->enviro));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_str(info->environ);
		info->environ = NULL;
		free_ptr((void **)info->cmd_buffer);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(BUF_FLUSH);
	}
}
