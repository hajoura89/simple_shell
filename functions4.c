#include "main.h"

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
