#include "main.h"

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
/**
 * _uunsetenv - Remove environment variable
 * @info: cmd info structure
 * Return: Always 0
 */
int _uunsetenv(cmdinfo_t *info)
{
	int i;

	if (info->argc == 1)
	{
		print_input_string("few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}
/**
 * _ssetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: cmd info structure
 * Return: Always 0
 */
int _ssetenv(cmdinfo_t *info)
{
	if (info->argc != 3)
	{
		print_input_string("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
