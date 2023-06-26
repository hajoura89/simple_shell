#include "main.h"
/**
 * write_to_fd - writes the character to file descriptor
 * @c:character to print
 * @fd: file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned
 */
int write_to_fd(char c, int fd)
{
	static int i;
	static char buf[BUFFER_WRITE];

	if (c == BUF_FLUSH || i >= BUFFER_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 *print_to_fd - prints an input string to file descriptor
 * @str: string to be printed
 * @fd: file descriptor to write to
 * Return: the number of chars put
 */
int print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_fd(*str++, fd);
	}
	return (i);
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
