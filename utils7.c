#include "main.h"
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
