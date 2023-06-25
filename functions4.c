#include "main.h"

/**
 * get_environ - returns copy of our environ
 * as string of array
 * @info: cmd info structure
 * Return: Always 0
 */
char **get_environ(cmdinfo_t *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = list_to_string(info->enviro);
		info->environ_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove environment variable
 * @info: cmd info structure
 * @var: env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(cmdinfo_t *info, char *var)
{
	list_t *node = info->enviro;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			info->environ_changed = delete_node_at(&(info->enviro), i);
			i = 0;
			node = info->enviro;
			continue;
		}
		node = node->nextnode;
		i++;
	}
	return (info->environ_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: cmd info structure
 * @var: env var property
 * @value: env var value
 * Return: Always 0
 */
int _setenv(cmdinfo_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->enviro;
	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->environ_changed = 1;
			return (0);
		}
		node = node->nextnode;
	}
	add_node_toend(&(info->enviro), buf, 0);
	free(buf);
	info->environ_changed = 1;
	return (0);
}

