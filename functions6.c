#include "main.h"

/**
 * is_chain_delimeter - test if current char in buffer is a chain delimeter
 * @info: cmd info structure
 * @buffer: the char buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_delimeter(cmdinfo_t *info, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		info->cmd_buffer_type = CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * chain_check - checks we should continue chaining based on last status
 * @info: cmd info structure
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 * @index: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void chain_check(cmdinfo_t *info, char *buffer, size_t *pos,
		size_t index, size_t len)
{
	size_t j = *pos;

	if (info->cmd_buffer_type == AND)
	{
		if (info->status)
		{
			buffer[index] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == OR)
	{
		if (!info->status)
		{
			buffer[index] = 0;
			j = len;
		}
	}

	*pos = j;
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

