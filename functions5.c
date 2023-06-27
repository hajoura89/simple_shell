#include "main.h"

/**
 * addto_history_list - adds entry to a history linked list
 * @info: cmd info structure
 * @buf: buffer
 * @linecount: the count
 * Return: Always 0
 */
int addto_history_list(cmdinfo_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_toend(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * get_hist_file - gets history file
 * @info: cmd info structure
 * Return: allocated string
 */
char *get_hist_file(cmdinfo_t *info)
{
	char *buf, *dir;

	dir = _getenvvalue(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}
/**
 * reindex_history - reindexes the history ll after changes
 * @info: cmd info structure
 * Return: the new count
 */
int reindex_history(cmdinfo_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->nextnode;
	}
	return (info->historycount = i);
}

