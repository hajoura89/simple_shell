#include "main.h"

/**
 * _currentenv - prints the current environment
 * @info: cmd info structure
 * Return: Always 0
 */
int _currentenv(cmdinfo_t *info)
{
	print_str_list(info->enviro);
	return (0);
}

/**
 * _getenvvalue - gets the value of an environ variable
 * @info: cmd info structure
 * @name: env var name
 * Return: the value
 */
char *_getenvvalue(cmdinfo_t *info, const char *name)
{
	list_t *node = info->enviro;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->nextnode;
	}
	return (NULL);
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
 * populate_envlist - populates env linked list
 * @info: cmd info structure
 * Return: Always 0
 */
int populate_envlist(cmdinfo_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_toend(&node, environ[i], 0);
	info->enviro = node;
	return (0);
}

