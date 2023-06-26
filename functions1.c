#include "main.h"
/**
 * read_buf - reads buffer
 * @info: cmd info structure
 * @buffer: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(cmdinfo_t *info, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->read_fd, buffer, BUFFER_READ);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * get_input - get input
 * @info: cmd info structure
 * Return: bytes read
 */
ssize_t get_input(cmdinfo_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_check(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain_delimeter(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buffer_type = NORMAL;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
