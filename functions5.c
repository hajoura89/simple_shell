#include "main.h"

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
 * create_history - creates a file, or appends to an existing one
 * @info: cmd info structure
 * Return: 1 on success, else -1
 */
int create_history(cmdinfo_t *info)
{
	ssize_t fd;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->nextnode)
	{
		print_to_fd(node->str, fd);
		write_to_fd('\n', fd);
	}
	write_to_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_historyfile - reads history from file
 * @info: cmd info structure
 * Return:count on success, 0 otherwise
 */
int read_historyfile(cmdinfo_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			addto_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		addto_history_list(info, buf + last, linecount++);
	free(buf);
	info->historycount = linecount;
	while (info->historycount-- >= HISTORY_MAX)
		delete_node_at(&(info->history), 0);
	reindex_history(info);
	return (info->historycount);
}

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

