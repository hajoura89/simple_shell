#include "main.h"

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 * replace_vars - replaces vars in the string
 * @info: cmd info structure
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(cmdinfo_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strduplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strduplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(info->enviro, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strduplicate(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strduplicate(""));

	}
	return (0);
}
/**
 * replace_alias - replaces aliases in the string
 * @info: cmd info structure
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(cmdinfo_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strduplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
