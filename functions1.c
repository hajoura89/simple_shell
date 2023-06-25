#include "main.h"

/**
 * input_buf - Input buffers
 * @info: cmd info structure
 * @buffer: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(cmdinfo_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSIGINT);
#if GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount = 1;
			remove_comments(*buffer);
			addto_history_list(info, *buffer, info->historycount++);
			{
				*len = r;
				info->cmd_buffer = buffer;
			}
		}
	}
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
 * _getline - gets the next line of input
 * @info: cmd info structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(cmdinfo_t *info, char **ptr, size_t *length)
{
	static char buf[BUFFER_READ];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handleSIGINT - Handles the SIGINT signal
 * blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void handleSIGINT(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

